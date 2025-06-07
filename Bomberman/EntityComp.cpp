#include "EntityComp.h"

#include "EntityStates.h"
#include "BMGameDefines.h"

bm::EntityComp::EntityComp(dae::GameObject& parent, const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller)
	:Component(parent)
	, m_pController{std::move(controller)}
	, m_pCurrentState{std::make_unique<IdleState>(parent)}
	, m_EntityStats{ entityStats }
{
	//check the controller
	if (!m_pController)
	{
		std::cout << std::format("Error: EntityComp initialized without a valid controller. [{}]\n", GetOwner().GetName());
		throw std::runtime_error("EntityComp: No controller given");
	}

	//make sure spritecomp is added before this comp!!!
	m_TransformComp.Init(GetOwner());
	m_SpriteComp.Init(GetOwner());
	m_SpriteComp->SetFPS(GLOBAL_FPS);	//todo, use the defines
	m_SpriteComp->SetAlignment(dae::HorizontalAlignment::center, dae::VerticalAlignment::center);
}

bm::EntityComp::~EntityComp() = default;

void bm::EntityComp::Start()
{
#ifdef _DEBUG
	m_pCurrentState->ValidateSprite();
#endif // _DEBUG

	m_SpriteComp->SetSpriteEntry(SPRITEID_MOVEDOWN);
	m_pCurrentState->OnEnter();
}

void bm::EntityComp::Update(float deltaTime)
{
	m_pController->Update(m_EntityCondition);

	UpdateState(deltaTime);
	m_EntityCondition.position = m_TransformComp->GetLocalPosition();
}

void bm::EntityComp::SetCommand1(std::unique_ptr<dae::Command>&& command)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->SetCommand1(std::move(command));
	}
	else
	{
		std::cout << std::format("Warning: EntityComp has no current state to set command1. [{}]\n", GetOwner().GetName());
	}
}

void bm::EntityComp::SetCommand2(std::unique_ptr<dae::Command>&& command)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->SetCommand2(std::move(command));
	}
	else
	{
		std::cout << std::format("Warning: EntityComp has no current state to set command2. [{}]\n", GetOwner().GetName());
	}
}

void bm::EntityComp::Kill()	//base behaviour
{
	m_pCurrentState->OnExit();
	auto deathState = std::make_unique<DeathState>(GetOwner());
	deathState->OnDeathComplete().AddObserver(this);
	m_pCurrentState = std::move(deathState);	//change to dead state
	m_pCurrentState->OnEnter();
}

void bm::EntityComp::UpdateState(float deltaTime)
{
	auto pNewState{ m_pCurrentState->Update(deltaTime, m_EntityStats) };
	if (!pNewState)
	{
		pNewState = m_pCurrentState->HandleInput(m_pController->GetInputRef());
	}
	if (pNewState)
	{
		m_pCurrentState->OnExit();	//call exit on the current state
		m_pCurrentState = std::move(pNewState);
		m_pCurrentState->OnEnter();

		m_EntityCondition.stateChanged = true;
		m_EntityCondition.stateType = m_pCurrentState->GetStateType();
	}
	else
	{
		m_EntityCondition.stateChanged = false;
	}
}

void bm::EntityComp::Notify(dae::Event event, const std::any&)
{
	if (event == DeathState::s_DeathComplete)
	{
		GetOwner().FlagForDeletion();
	}
}
