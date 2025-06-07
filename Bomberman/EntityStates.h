#ifndef ENTITYSTATES_H
#define ENTITYSTATES_H

#include <EngineComponents.h>
#include <memory>

#include <Command.h>
#include <Subject.h>

#include "EntityComp.h"
#include "EntityUtils.h"

namespace bm
{
	class EntityState
	{
	public:
		EntityState(dae::GameObject& gObj, EntityStateType type);
		virtual ~EntityState() = default;

		virtual void OnEnter() {};
		virtual void OnExit() {};

		virtual std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data) = 0;
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input) = 0;

		virtual void SetCommand1(std::unique_ptr<dae::Command>&& command);
		virtual void SetCommand2(std::unique_ptr<dae::Command>&& command);

		EntityStateType GetStateType() const;

		void ValidateSprite();	//helper to test if the sprite has been set correctly

	protected:

		void SetCommands(EntityState* state);	//for internal usage so commands are auto transferred

		//===============================
		std::unique_ptr<dae::Command> m_pCommand1;	//executes if Action1 == true (from EntityInput)
		std::unique_ptr<dae::Command> m_pCommand2;	//executes if Action1 == true (from EntityInput)

		dae::GameObject& m_GameObject;
		EntityStateType m_StateType;
	};

	//=================================================================================================================================
	//Movement Base 
	//=================================================================================================================================

	class MovementState : public EntityState	//Update not implemented -> pure virtual
	{
	public:
		MovementState(dae::GameObject& gObj, EntityStateType type);
		virtual ~MovementState() = default;

		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);	//only handles Action1 and Action2, and sets the stored input (so update can use it for fluid state transitions)

	protected:

		std::unique_ptr<EntityState> GetNewDirectionState(glm::ivec2 direction);	//helper function for all derived classes

		//===============================

		glm::ivec2 m_StoredDirection{};

		dae::TransformComp& m_TransformComp;
		dae::SpriteComp& m_SpriteComp;
	};

	//=================================================================================================================================
	//Movement Directions 
	//=================================================================================================================================

	class IdleState final : public MovementState
	{
	public:
		IdleState(dae::GameObject& gObj);

		void OnEnter() override;
		void OnExit() override;

		std::unique_ptr<EntityState> Update(float, EntityStats&) override { return nullptr; };
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);

	};

	//=================
	class MoveUpState final : public MovementState
	{
	public:
		MoveUpState(dae::GameObject& gObj, float targetY);

		void OnEnter() override;

		virtual std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data);
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);

	private:
		float m_TargetY;
	};

	//=================
	class MoveDownState final : public MovementState
	{
	public:
		MoveDownState(dae::GameObject& gObj, float targetY);

		void OnEnter() override;

		virtual std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data);
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);

	private:
		float m_TargetY;
	};

	//=================
	class MoveRightState final : public MovementState
	{
	public:
		MoveRightState(dae::GameObject& gObj, float targetX);

		void OnEnter() override;
		void OnExit() override;

		virtual std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data);
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);

	private:
		float m_TargetX;
	};

	//=================
	class MoveLeftState final : public MovementState
	{
	public:
		MoveLeftState(dae::GameObject& gObj, float targetX);

		void OnEnter() override;

		virtual std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data);
		virtual std::unique_ptr<EntityState> HandleInput(EntityInput& input);

	private:
		float m_TargetX;
	};

//=================================================================================================================================
//Death
//=================================================================================================================================

	class DeathState final : public EntityState
	{
	public:

		DeathState(dae::GameObject& gObj);

		void OnEnter() override;

		std::unique_ptr<EntityState> Update(float deltaTime, EntityStats& data);
		std::unique_ptr<EntityState> HandleInput(EntityInput&) { return nullptr; };

		dae::Subject& OnDeathComplete();

		static constexpr dae::Event s_DeathComplete = dae::Event("DeathComplete");

	private:

		dae::SpriteComp& m_SpriteComp;
		dae::Subject m_DeathCompleteSubject;
		bool m_SubjectCalled{ false };
	};

}
#endif // !ENTITYSTATES_H

