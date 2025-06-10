#ifndef ENEMYCOMP_H
#define ENEMYCOMP_H

#include "Component.h"

#include <EngineComponents.h>
#include <IObserver.h>

namespace bm
{
	class EnemyComp final : public dae::Component, public dae::IObserver	//Args: 
	{
	public:
		EnemyComp(dae::GameObject& parent);

		EnemyComp(const EnemyComp& other) = default;
		EnemyComp(EnemyComp&& other) noexcept = default;
		EnemyComp& operator=(const EnemyComp& other) = default;
		EnemyComp& operator=(EnemyComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------



	private:

		static constexpr float s_HitRadius{ 12.f };	

		dae::ReqComp<dae::SimpleCollisionComp> m_SimpleCollisionComp{};

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

	};
}
#endif // !ENEMYCOMP_H