#ifndef BASEENTITYCOMP_H
#define BASEENTITYCOMP_H

#include "Component.h"

#include <glm.hpp>
#include <memory>
#include <EngineComponents.h>

namespace bm
{
	class EntityState;

	struct EntityStats
	{
		float movementSpeed;

	};

	struct EntityInput
	{
		glm::ivec2 direction;
		bool action1;
		bool action2;
	};

	class BaseEntityComp : public dae::Component	//Args: const EntityStats& entityStats
	{
	public:
		BaseEntityComp(dae::GameObject& parent, const EntityStats& entityStats);

		virtual ~BaseEntityComp(); //defulted in cpp
		BaseEntityComp(const BaseEntityComp& other) = default;
		BaseEntityComp(BaseEntityComp&& other) noexcept = default;
		BaseEntityComp& operator=(const BaseEntityComp& other) = default;
		BaseEntityComp& operator=(BaseEntityComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		virtual void Kill();

	protected:

		bool UpdateState(float deltaTime);	//return if the state has been changed

		//==========================

		std::unique_ptr<EntityState> m_pCurrentState;
		dae::ReqComp<dae::TransformComp> m_TransformComp{};
		dae::ReqComp<dae::SpriteComp> m_SpriteComp{};

		EntityStats m_EntityStats;
		EntityInput m_EntityInput{};

	};
}
#endif // !BASEENTITYCOMP_H