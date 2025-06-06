#include "TileMod.h"

#include <GameObject.h>
#include "BMServiceLocator.h"

bm::TileMod::TileMod(dae::GameObject& object, TileModId id)
	: m_Object{ object }
	, m_Id{ id }
{
	auto& tileService = BMServiceLocator::GetTileSystem();
	auto* pTile = tileService.GetTileFromWorldPos(object.GetWorldPos());

	if (pTile)
	{
		pTile->RegisterTileMod(this);
		m_Registered = true;
	}
}

bm::TileModId bm::TileMod::GetId() const
{
	return m_Id;
}

void bm::TileMod::Unregister()
{
	if (!m_Registered)
		return;

	auto& tileService = BMServiceLocator::GetTileSystem();
	auto* pTile = tileService.GetTileFromWorldPos(m_Object.GetWorldPos());

	if (pTile)
	{
		pTile->UnregisterTileMod(this);
		m_Registered = false;
	}
}
