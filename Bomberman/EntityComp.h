#ifndef ENTITYCOMP_H
#define ENTITYCOMP_H

#include "Component.h"

#include <glm.hpp>
#include <memory>
#include <EngineComponents.h>
#include <IObserver.h>
#include <Command.h>

#include "EntityUtils.h"

#include "EntityController.h"

namespace bm
{
	class EntityState;

	class EntityComp final : public dae::Component, public dae::IObserver	//Args: const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller
	{
	public:
		EntityComp(dae::GameObject& parent, const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller);

		~EntityComp(); //defaulted in cpp
		EntityComp(const EntityComp& other) = default;
		EntityComp(EntityComp&& other) noexcept = default;
		EntityComp& operator=(const EntityComp& other) = default;
		EntityComp& operator=(EntityComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		void SetCommand1(std::unique_ptr<dae::Command>&& command);
		void SetCommand2(std::unique_ptr<dae::Command>&& command);

		void Kill();

	protected:

		void UpdateState(float deltaTime);	//return if the state has been changed

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

		//==========================

		std::unique_ptr<EntityController> m_pController;
		std::unique_ptr<EntityState> m_pCurrentState;
		dae::ReqComp<dae::TransformComp> m_TransformComp{};
		dae::ReqComp<dae::SpriteComp> m_SpriteComp{};

		EntityStats m_EntityStats;
		EntityCondition m_EntityCondition{};
	};
}
#endif // !ENTITYCOMP_H