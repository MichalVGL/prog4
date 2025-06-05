#include "TileMod.h"

#include <GameObject.h>
#include "BMServiceLocator.h"

bm::TileMod::TileMod(TileModId id, dae::GameObject& object)
	: m_Id{ id }
	, m_Object{ object }
{
	//todo, maybe register here
	auto& tileService = BMServiceLocator::GetTileSystem();
	auto* pTile = tileService.GetTileFromWorldPos(object.GetWorldPos());

	pTile->RegisterTileMod(this);
}

bm::TileModId bm::TileMod::GetId() const
{
	return m_Id;
}

void bm::TileMod::Unregister()
{
	auto& tileService = BMServiceLocator::GetTileSystem();
	auto* pTile = tileService.GetTileFromWorldPos(m_Object.GetWorldPos());

	pTile->UnregisterTileMod(this);
}
