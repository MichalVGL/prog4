#ifndef TILECOMP_H
#define TILECOMP_H

#include "Component.h"

#include <glm.hpp>
#include <Texture.h>
#include <EngineComponents.h>

#include "BaseTile.h"
#include "TileMod.h"

namespace bm
{
	class TileComp final : public dae::Component	//Args: BaseTile* pBaseTile, ivec2 indexPos
	{
	public:
		TileComp(dae::GameObject& parent, const BaseTile* pBaseTile, glm::ivec2 indexPos);

		~TileComp() = default;
		TileComp(const TileComp& other) = default;
		TileComp(TileComp&& other) noexcept = default;
		TileComp& operator=(const TileComp& other) = default;
		TileComp& operator=(TileComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		glm::vec2 GetPosition();
		glm::ivec2 GetIndexPosition();

		bool IsWalkable() const;
		bool AllowSpawnables() const;

		bool HasTileMod() const;	//returns the tilemodid if it exists, otherwise returns nullptr
		const TileMod* GetTileMod() const;	//returns the tilemodid if it exists, otherwise returns nullptr
		TileMod* GetTileMod();	//non const version

		void RegisterTileMod(TileMod* pTileMod);
		void UnregisterTileMod(TileMod* pTileMod);

		TileComp* GetUpTile() const;
		TileComp* GetRightTile() const;
		TileComp* GetDownTile() const;
		TileComp* GetLeftTile() const;

		void SetAdjescentTiles(TileComp* up, TileComp* right, TileComp* down, TileComp* left);	//should only be used for setup. (in the tilesystem)

	private:


		//========================================================================

		dae::ReqComp<dae::TransformComp> m_TransformComp;
		dae::ReqComp<dae::RenderComp> m_RenderComp;

		const BaseTile* m_pBaseTile;
		TileMod* m_pTileMod{};

		const glm::ivec2 m_IndexPos;
		const glm::vec2 m_Pos;

		TileComp* m_pUpTile{};
		TileComp* m_pRightTile{};
		TileComp* m_pDownTile{};
		TileComp* m_pLeftTile{};

	};
}
#endif // !TILECOMP_H