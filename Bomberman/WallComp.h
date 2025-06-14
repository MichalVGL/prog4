#ifndef WALLCOMP_H
#define WALLCOMP_H

#include "Component.h"

#include <EngineComponents.h>
#include <Texture.h>

#include "TileMod.h"
#include "BMGameDefines.h"

namespace bm
{
	enum class ContainedObject
	{
		none,
		upgrade,
		door
	};

	class WallComp final : public dae::Component, public TileMod	//Args: ContainedObject object = ContainedObject::none
	{
	public:
		WallComp(dae::GameObject& parent, ContainedObject object = ContainedObject::none);

		WallComp(const WallComp& other) = default;
		WallComp(WallComp&& other) noexcept = default;
		WallComp& operator=(const WallComp& other) = default;
		WallComp& operator=(WallComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		void OnDestroy() override;
		//--------------------------

		void DestroyWall();

	private:

		static constexpr dae::TextureEntry s_WallTextureEntry{ "Textures/Wall.png" };
		static constexpr dae::SpriteEntry s_BaseWallSprite{ "Normal", {0, 0, TILE_SIZE, TILE_SIZE}, 1, 1, false };
		static constexpr dae::SpriteEntry s_DestroyingWallSprite{ "Destroying", {TILE_SIZE, 0, TILE_SIZE * 6, TILE_SIZE}, 6, 1, false };

		dae::ReqComp<dae::SpriteComp> m_SpriteComp{};

		bool m_IsBeingDestroyed{ false };

		ContainedObject m_ContainedObject;

		// Inherited via TileMod
		bool IsWalkable() const override;
	};
}
#endif // !WALLCOMP_H