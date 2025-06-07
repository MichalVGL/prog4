#ifndef FIRECOMP_H
#define FIRECOMP_H

#include "Component.h"

#include <vector>

#include <Texture.h>
#include <IObserver.h>

#include "TileComp.h"
#include "TileMod.h"
#include "BMGameDefines.h"
#include "BMUtils.h"
#include "TileCollisionComp.h"


namespace bm
{

	class FireComp final : public dae::Component, public dae::IObserver 	//Args: std::vector<dae::GameObjectHandle> targets, FireComp::Direction direction, int spreadAmount
	{
	public:

		FireComp(dae::GameObject& parent, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount);

		FireComp(const FireComp& other) = default;
		FireComp(FireComp&& other) noexcept = default;
		FireComp& operator=(const FireComp& other) = default;
		FireComp& operator=(FireComp&& other) noexcept = default;

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



	private:

		static constexpr dae::TextureEntry s_FireTexture{ "Fire.png" };

		static constexpr dae::SpriteEntry s_OmniSprite{ "OmniFire", {0, 0, TILE_SIZE * 7, TILE_SIZE}, 7, 1, false };
		static constexpr dae::SpriteEntry s_ConnectedSprite{ "ConnectedFire", {0, TILE_SIZE, TILE_SIZE * 7, TILE_SIZE}, 7, 1, false };
		static constexpr dae::SpriteEntry s_EndSprite{ "EndFire", {0, TILE_SIZE * 2, TILE_SIZE * 7, TILE_SIZE}, 7, 1, false };

		dae::ReqComp<dae::SpriteComp> m_SpriteComp{};
		dae::ReqComp<TileCollisionComp> m_TileCollisionComp{};

		//these function automatically check if the tile is valid to spawn fire / detonate other bombs
		void HandleNextTile(std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount);
		void HandleAllAdjacentTiles(std::vector<dae::GameObjectHandle> targets, int spreadAmount);


		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

		void HandleEntityCollision(const dae::GameObjectHandle& handle);

	};
}
#endif // !FIRECOMP_H