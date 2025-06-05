#ifndef BASEENTITYCOMP_H
#define BASEENTITYCOMP_H

#include "Component.h"

#include <glm.hpp>
#include <memory>
#include <EngineComponents.h>

#include "EntityUtils.h"

#include "EntityController.h"

namespace bm
{
	class EntityState;

	class BaseEntityComp final : public dae::Component	//Args: const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller
	{
	public:
		BaseEntityComp(dae::GameObject& parent, const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller);

		~BaseEntityComp(); //defaulted in cpp
		//BaseEntityComp(const BaseEntityComp& other) = default;
		//BaseEntityComp(BaseEntityComp&& other) noexcept = default;
		//BaseEntityComp& operator=(const BaseEntityComp& other) = default;
		//BaseEntityComp& operator=(BaseEntityComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		void Kill();

	protected:

		void UpdateState(float deltaTime);	//return if the state has been changed

		//==========================

		std::unique_ptr<EntityController> m_pController;
		std::unique_ptr<EntityState> m_pCurrentState;
		dae::ReqComp<dae::TransformComp> m_TransformComp{};
		dae::ReqComp<dae::SpriteComp> m_SpriteComp{};

		EntityStats m_EntityStats;
		//EntityInput m_EntityInput{};
		EntityCondition m_EntityCondition{};
	};
}
#endif // !BASEENTITYCOMP_H