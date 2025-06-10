#ifndef COMP_H
#define COMP_H

#include "Component.h"

#include "Event.h"
#include "Subject.h"

namespace dae
{
	class SimpleCollisionComp final : public dae::Component	//Args: 
	{
	public:
		SimpleCollisionComp(dae::GameObject& parent);

		~SimpleCollisionComp() = default;
		SimpleCollisionComp(const SimpleCollisionComp& other) = default;
		SimpleCollisionComp(SimpleCollisionComp&& other) noexcept = default;
		SimpleCollisionComp& operator=(const SimpleCollisionComp& other) = default;
		SimpleCollisionComp& operator=(SimpleCollisionComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

		void SetRadius(float radius);

		void AddTarget(dae::GobjID targetId);
		void RemoveTarget(dae::GobjID targetId);

		void UpdateTargets();

		dae::Subject& OnCollision();

		static constexpr dae::Event s_CollisionEvent = dae::Event("SimpleCollision");

	private:

		void SetTargets();
		void CleanupTargets();	//checks if any handle is invalid and removes it from the vector

		float m_Radius{ 1.f };

		std::vector<dae::GobjID> m_TargetIds{};	// IDs of the targets
		std::vector<dae::GameObjectHandle> m_Targets{};	//object instance to check for collision
		bool m_TargetsDirty{ false };	//if the targets need to be updated

		dae::Subject m_CollisionSubject{ s_CollisionEvent };
	};
}
#endif // !COMP_H