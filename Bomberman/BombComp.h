#ifndef BOMBCOMP_H
#define BOMBCOMP_H

#include "Component.h"
#include <EngineComponents.h>
#include <IObserver.h>

#include "TileMod.h"
#include "TimerComp.h"

#include "BMGameDefines.h"

namespace bm
{
	class BombComp final : public dae::Component, public TileMod, public dae::IObserver		//Args: 
	{
	public:
		BombComp(dae::GameObject& parent);

		BombComp(const BombComp& other) = delete;
		BombComp(BombComp&& other) noexcept = delete;
		BombComp& operator=(const BombComp& other) = delete;
		BombComp& operator=(BombComp&& other) noexcept = delete;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		void OnDestroy() override;
		//--------------------------

		void Detonate();

	private:

		//==============================

		static constexpr float s_DetonationTime{ 2.5f };
		static constexpr dae::TextureEntry s_BombTextureEntry{ "Textures/Bomb.png" };
		static constexpr dae::SpriteEntry s_BombSpriteEntry{ "BaseBomb", { 0, 0, TILE_SIZE * 4, TILE_SIZE }, 4, 1 };

		dae::ReqComp<TimerComp> m_TimerComp;
		dae::ReqComp<dae::SpriteComp> m_SpriteComp;

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

		// Inherited via TileMod
		bool IsWalkable() const override;
	};
}
#endif // !BOMBCOMP_H