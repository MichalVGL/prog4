#ifndef TILECOLLISIONCOMP_H
#define TILECOLLISIONCOMP_H

#include "Component.h"

#include <Subject.h>

namespace bm
{
	class TileCollisionComp final : public dae::Component	//Args: 
	{
	public:
		TileCollisionComp(dae::GameObject& parent);

		TileCollisionComp(const TileCollisionComp& other) = default;
		TileCollisionComp(TileCollisionComp&& other) noexcept = default;
		TileCollisionComp& operator=(const TileCollisionComp& other) = default;
		TileCollisionComp& operator=(TileCollisionComp&& other) noexcept = default;

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

		void AddTarget(dae::GobjID targetId);
		void RemoveTarget(dae::GobjID targetId);

		void UpdateTargets();

		dae::Subject& OnCollision();

		static constexpr dae::Event s_CollisionEvent = dae::Event("TileCollision");

	private:

		void SetTargets();
		void CleanupTargets();	//checks if any handle is invalid and removes it from the vector

		std::vector<dae::GobjID> m_TargetIds{};	// IDs of the targets
		std::vector<dae::GameObjectHandle> m_Targets{};	//object instance to check for collision
		bool m_TargetsDirty{ false };	//if the targets need to be updated

		dae::Subject m_CollisionSubject{s_CollisionEvent};
	};
}
#endif // !TILECOLLISIONCOMP_H