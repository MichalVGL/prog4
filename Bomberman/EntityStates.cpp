#include "EntityStates.h"

#include <iostream>

#include "BMGameDefines.h" 
#include "BMServiceLocator.h"

bm::EntityState::EntityState(dae::GameObject& gObj, EntityStateType type)
	:m_GameObject{ gObj }
	, m_StateType{ type }
{
}

void bm::EntityState::SetCommand1(std::unique_ptr<dae::Command>&& command)
{
	m_pCommand1 = std::move(command);
}

void bm::EntityState::SetCommand2(std::unique_ptr<dae::Command>&& command)
{
	m_pCommand2 = std::move(command);
}

bm::EntityStateType bm::EntityState::GetStateType() const
{
	return m_StateType;
}

//HELPERS===================

//public

void bm::EntityState::ValidateSprite()
{
	auto spriteComp = m_GameObject.GetComponent<dae::SpriteComp>();

	if (spriteComp->GetSpriteEntry(SPRITEID_MOVEUP) == nullptr or
		spriteComp->GetSpriteEntry(SPRITEID_MOVELEFT) == nullptr or
		spriteComp->GetSpriteEntry(SPRITEID_MOVEDOWN) == nullptr or
		spriteComp->GetSpriteEntry(SPRITEID_DEATH) == nullptr)
	{
		std::cout << std::format("Warning: Cannot find a required sprite_id on the given spriteComp. [GameObject: {}]", spriteComp->GetOwner().GetName());
	}
}

//private

void bm::EntityState::SetCommands(EntityState* newState)
{
	if (newState)
	{
		newState->SetCommand1(std::move(m_pCommand1));
		newState->SetCommand2(std::move(m_pCommand2));
	}
}

//=================================================================================================================================
//Implementations
//=================================================================================================================================

//=========================================================
//MovementState (base class for implementations)
//=========================================================

bm::MovementState::MovementState(dae::GameObject& gObj, EntityStateType type)
	:EntityState{ gObj, type }
	, m_TransformComp{ *gObj.GetComponent<dae::TransformComp>() }
	, m_SpriteComp{ *gObj.GetComponent<dae::SpriteComp>() }
{
}

std::unique_ptr<bm::EntityState> bm::MovementState::HandleInput(EntityInput& input)
{
	if (input.action1)
	{
		if (m_pCommand1)
			m_pCommand1->Execute();
		input.action1 = false;	//"consume" the action
	}

	if (input.action2)
	{
		if (m_pCommand2)
			m_pCommand2->Execute();
		input.action2 = false;	//"consume" the action
	}

	m_StoredDirection = input.direction;

	return nullptr;
}

//HELPERS===================

std::unique_ptr<bm::EntityState> bm::MovementState::GetNewDirectionState(glm::ivec2 direction)
{
	//todo, use servicelocator to get to tiles, the levelcomp inits and destroys the service. Use the helper function on the service to get validation here

	auto& tileService{ BMServiceLocator::GetTileSystem() };
	auto* currentTile{ tileService.GetTileFromWorldPos(m_TransformComp.GetOwner().GetWorldPos()) };

	if (currentTile == nullptr)
	{
		return nullptr;	//no current tile found, cannot move
	}

	TileComp* pNextTile{};
	switch (direction.x)
	{
	case 1:
		pNextTile = currentTile->GetRightTile();
		if (pNextTile && pNextTile->IsWalkable())
		{
			return std::make_unique<bm::MoveRightState>(m_GameObject, pNextTile->GetPosition().x);
		}
		break;
	case -1:
		pNextTile = currentTile->GetLeftTile();
		if (pNextTile && pNextTile->IsWalkable())
		{
			return std::make_unique<bm::MoveLeftState>(m_GameObject, pNextTile->GetPosition().x);
		}
		break;
	}

	switch (direction.y)
	{
	case 1:
		pNextTile = currentTile->GetUpTile();
		if (pNextTile && pNextTile->IsWalkable())
		{
			return std::make_unique<bm::MoveUpState>(m_GameObject, pNextTile->GetPosition().y);
		}
		break;
	case -1:
		pNextTile = currentTile->GetDownTile();
		if (pNextTile && pNextTile->IsWalkable())
		{
			return std::make_unique<bm::MoveDownState>(m_GameObject, pNextTile->GetPosition().y);
		}
	}

	return nullptr;
}

//=======================================================================
//IdleState
//=======================================================================

bm::IdleState::IdleState(dae::GameObject& gObj)
	:MovementState{ gObj, EntityStateType::Idle }
{
}

void bm::IdleState::OnEnter()
{
	m_SpriteComp.Pause();
	m_SpriteComp.SetFrame(IDLEFRAME);
}

void bm::IdleState::OnExit()
{
	m_SpriteComp.Resume();
}

std::unique_ptr<bm::EntityState> bm::IdleState::HandleInput(EntityInput& input)
{
	MovementState::HandleInput(input);
	auto pNewState{ GetNewDirectionState(input.direction) };
	if (pNewState)
	{
		SetCommands(pNewState.get());	//transfer commands to the new state
		return pNewState;
	}
	return nullptr;
}

//=======================================================================
//MoveUpState
//=======================================================================

bm::MoveUpState::MoveUpState(dae::GameObject& gObj, float targetY)
	:MovementState{ gObj, EntityStateType::Moving }
	, m_TargetY{ targetY }
{
}

void bm::MoveUpState::OnEnter()
{
	m_SpriteComp.FlipHorizontal(false);	//reset the flip, if it was set by the MoveRightState
	m_SpriteComp.SetSpriteEntry(SPRITEID_MOVEUP);
}

std::unique_ptr<bm::EntityState> bm::MoveUpState::Update(float deltaTime, EntityStats& data)
{
	auto pos = m_TransformComp.GetLocalPosition();
	pos.y += data.movementSpeed * deltaTime;

	if (pos.y > m_TargetY)	//newState completed
	{
		pos.y = m_TargetY;
		m_TransformComp.SetLocalPosition(pos);

		//switch to another direction or go to idle
		auto pNewState{ GetNewDirectionState(m_StoredDirection) };
		if (pNewState == nullptr)	//no direction given in input
		{
			pNewState = std::make_unique<bm::IdleState>(m_GameObject);
		}
		SetCommands(pNewState.get());	//todo, call this in every return newState case
		return pNewState;
	}
	else
	{
		m_TransformComp.SetLocalPosition(pos);
	}

	return nullptr;
}

std::unique_ptr<bm::EntityState> bm::MoveUpState::HandleInput(EntityInput& input)
{
	MovementState::HandleInput(input);

	if (input.direction.y == -1)	//if you want to go back mid transition
	{
		auto& tileService{ BMServiceLocator::GetTileSystem() };
		auto* pTargetTile{ tileService.GetTileFromWorldPos({ m_TransformComp.GetLocalPosition().x, m_TargetY }) };	//current target
		auto* pNextTile{ pTargetTile ? pTargetTile->GetDownTile() : nullptr };	//potential next tile
		if (pNextTile && pNextTile->IsWalkable())
		{
			auto pNewState{ std::make_unique<bm::MoveDownState>(m_GameObject, pNextTile->GetPosition().y) };
			SetCommands(pNewState.get());	//transfer commands to the new state
			return pNewState;
		}
	}
	return nullptr;
}

//=======================================================================
//MoveDownState
//=======================================================================

bm::MoveDownState::MoveDownState(dae::GameObject& gObj, float targetY)
	:MovementState{ gObj, EntityStateType::Moving }
	, m_TargetY{ targetY }
{
}

void bm::MoveDownState::OnEnter()
{
	m_SpriteComp.FlipHorizontal(false);	//reset the flip, if it was set by the MoveRightState
	m_SpriteComp.SetSpriteEntry(SPRITEID_MOVEDOWN);
}

std::unique_ptr<bm::EntityState> bm::MoveDownState::Update(float deltaTime, EntityStats& data)
{
	auto pos = m_TransformComp.GetLocalPosition();
	pos.y -= data.movementSpeed * deltaTime;

	if (pos.y < m_TargetY)	//newState completed
	{
		pos.y = m_TargetY;
		m_TransformComp.SetLocalPosition(pos);

		//switch to another direction or go to idle
		auto pNewState{ GetNewDirectionState(m_StoredDirection) };
		if (pNewState == nullptr)	//no direction given in input
		{
			pNewState = std::make_unique<bm::IdleState>(m_GameObject);
		}
		SetCommands(pNewState.get());	//todo, call this in every return newState case
		return pNewState;
	}
	else
	{
		m_TransformComp.SetLocalPosition(pos);
	}

	return nullptr;
}

std::unique_ptr<bm::EntityState> bm::MoveDownState::HandleInput(EntityInput& input)
{
	MovementState::HandleInput(input);

	if (input.direction.y == 1)	//if you want to go back mid transition
	{
		auto& tileService{ BMServiceLocator::GetTileSystem() };
		auto* pTargetTile{ tileService.GetTileFromWorldPos({ m_TransformComp.GetLocalPosition().x, m_TargetY }) };	//current target
		auto* pNextTile{ pTargetTile ? pTargetTile->GetUpTile() : nullptr };	//potential next tile
		if (pNextTile && pNextTile->IsWalkable())
		{
			auto pNewState{ std::make_unique<bm::MoveUpState>(m_GameObject, pNextTile->GetPosition().y) };
			SetCommands(pNewState.get());	//transfer commands to the new state
			return pNewState;
		}
	}
	return nullptr;
}

//=======================================================================
//MoveRightState
//=======================================================================

bm::MoveRightState::MoveRightState(dae::GameObject& gObj, float targetX)
	:MovementState{ gObj, EntityStateType::Moving }
	, m_TargetX{ targetX }
{
}

void bm::MoveRightState::OnEnter()
{
	m_SpriteComp.SetSpriteEntry(SPRITEID_MOVELEFT);
	m_SpriteComp.FlipHorizontal(true);	//flip the sprite to the right
}

void bm::MoveRightState::OnExit()
{
}

std::unique_ptr<bm::EntityState> bm::MoveRightState::Update(float deltaTime, EntityStats& data)
{
	auto pos = m_TransformComp.GetLocalPosition();
	pos.x += data.movementSpeed * deltaTime;

	if (pos.x > m_TargetX)	//newState completed
	{
		pos.x = m_TargetX;
		m_TransformComp.SetLocalPosition(pos);

		//switch to another direction or go to idle
		auto pNewState{ GetNewDirectionState(m_StoredDirection) };
		if (pNewState == nullptr)	//no direction given in input
		{
			pNewState = std::make_unique<bm::IdleState>(m_GameObject);
		}
		SetCommands(pNewState.get());	//todo, call this in every return newState case
		return pNewState;
	}
	else
	{
		m_TransformComp.SetLocalPosition(pos);
	}

	return nullptr;
}

std::unique_ptr<bm::EntityState> bm::MoveRightState::HandleInput(EntityInput& input)
{
	MovementState::HandleInput(input);

	if (input.direction.x == -1)	//if you want to go back mid transition
	{
		auto& tileService{ BMServiceLocator::GetTileSystem() };
		auto* pTargetTile{ tileService.GetTileFromWorldPos({m_TargetX, m_TransformComp.GetLocalPosition().y}) };	//current target
		auto* pNextTile{ pTargetTile ? pTargetTile->GetLeftTile() : nullptr };	//potential next tile
		if (pNextTile && pNextTile->IsWalkable())
		{
			auto pNewState{ std::make_unique<bm::MoveLeftState>(m_GameObject, pNextTile->GetPosition().x) };
			SetCommands(pNewState.get());	//transfer commands to the new state
			return pNewState;
		}
	}
	return nullptr;
}

//=======================================================================
//MoveLeftState
//=======================================================================

bm::MoveLeftState::MoveLeftState(dae::GameObject& gObj, float targetX)
	:MovementState{ gObj, EntityStateType::Moving }
	, m_TargetX{ targetX }
{
}

void bm::MoveLeftState::OnEnter()
{
	m_SpriteComp.FlipHorizontal(false);	//reset the flip, if it was set by the MoveRightState
	m_SpriteComp.SetSpriteEntry(SPRITEID_MOVELEFT);
}

std::unique_ptr<bm::EntityState> bm::MoveLeftState::Update(float deltaTime, EntityStats& data)
{
	auto pos = m_TransformComp.GetLocalPosition();
	pos.x -= data.movementSpeed * deltaTime;

	if (pos.x < m_TargetX)	//newState completed
	{
		pos.x = m_TargetX;
		m_TransformComp.SetLocalPosition(pos);

		//switch to another direction or go to idle
		auto pNewState{ GetNewDirectionState(m_StoredDirection) };
		if (pNewState == nullptr)	//no direction given in input
		{
			pNewState = std::make_unique<bm::IdleState>(m_GameObject);
		}
		SetCommands(pNewState.get());	//todo, call this in every return newState case
		return pNewState;
	}
	else
	{
		m_TransformComp.SetLocalPosition(pos);
	}

	return nullptr;
}

std::unique_ptr<bm::EntityState> bm::MoveLeftState::HandleInput(EntityInput& input)
{
	MovementState::HandleInput(input);

	if (input.direction.x == 1)	//if you want to go back mid transition
	{
		auto& tileService{ BMServiceLocator::GetTileSystem() };
		auto* pTargetTile{ tileService.GetTileFromWorldPos({ m_TargetX, m_TransformComp.GetLocalPosition().y }) };	//current target
		auto* pNextTile{ pTargetTile ? pTargetTile->GetRightTile() : nullptr };	//potential next tile
		if (pNextTile && pNextTile->IsWalkable())
		{
			auto pNewState{ std::make_unique<bm::MoveRightState>(m_GameObject, pNextTile->GetPosition().x) };
			SetCommands(pNewState.get());	//transfer commands to the new state
			return pNewState;
		}
	}
	return nullptr;
}

//=======================================================================
//DeathState
//=======================================================================

bm::DeathState::DeathState(dae::GameObject& gObj)
	:EntityState{ gObj, EntityStateType::Dying }
	, m_SpriteComp{ *gObj.GetComponent<dae::SpriteComp>() }
	, m_DeathCompleteSubject{ s_DeathComplete }
{
}

void bm::DeathState::OnEnter()
{
	m_SpriteComp.SetSpriteEntry(SPRITEID_DEATH);
}

std::unique_ptr<bm::EntityState> bm::DeathState::Update(float, EntityStats&)
{
	if (m_SubjectCalled == false)
	{
		if (m_SpriteComp.IsLoopComplete())
			m_DeathCompleteSubject.NotifyObservers();
	}

	return nullptr;
}

dae::Subject& bm::DeathState::OnDeathComplete()
{
	return m_DeathCompleteSubject;
}