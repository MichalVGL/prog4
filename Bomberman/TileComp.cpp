#include "TileComp.h"

#include "BMGameDefines.h"

bm::TileComp::TileComp(dae::GameObject& parent, const BaseTile* pBaseTile, glm::ivec2 posIndex)
	:Component{ parent }
	, m_pBaseTile{ pBaseTile }
	, m_IndexPos{ posIndex }
	, m_Pos{ static_cast<float>(TILE_SIZE / 2 + TILE_SIZE * posIndex.x), static_cast<float>(TILE_SIZE / 2 + TILE_SIZE * posIndex.y) }
{
	if (m_pBaseTile == nullptr)
	{
		std::cout << std::format("TileComp: Tried to initialize TileComp with nullptr at index ({}, {})\n", posIndex.x, posIndex.y);
		throw std::runtime_error("TileComp: BaseTile pointer is null");
	}

	m_TransformComp.Init(GetOwner());
	m_TransformComp->SetLocalPosition(m_Pos);

	m_RenderComp.Init(GetOwner());
	m_RenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	m_RenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	m_RenderComp->LoadImageTexture(m_pBaseTile->GetTextureEntry());
}

glm::vec2 bm::TileComp::GetPosition()
{
	return m_Pos;
}

glm::ivec2 bm::TileComp::GetIndexPosition()
{
	return m_IndexPos;
}

bool bm::TileComp::IsWalkable() const
{
	if (m_pTileMod)
	{
		return m_pTileMod->IsWalkable() && m_pBaseTile->IsWalkable();
	}
	else
	{
		return m_pBaseTile->IsWalkable();
	}
}

bool bm::TileComp::HasTileMod() const
{
	return m_pTileMod != nullptr;
}

const bm::TileMod* bm::TileComp::GetTileMod() const
{
	return m_pTileMod;
}

bm::TileMod* bm::TileComp::GetTileMod()
{
	return m_pTileMod;
}

void bm::TileComp::RegisterTileMod(TileMod* pTileMod)
{
	if (m_pTileMod != nullptr)
	{
		std::cout << std::format("TileComp: Tried to register a TileMod ({}) on tile ({}, {}) that already has a TileMod\n", typeid(*pTileMod).name(), m_IndexPos.x, m_IndexPos.y);
		return;
	}
	m_pTileMod = pTileMod;
}

void bm::TileComp::UnregisterTileMod(TileMod* pTileMod)
{
	if (m_pTileMod == nullptr)
	{
		std::cout << std::format("TileComp: Tried to unregister a TileMod on tile ({}, {}) that does not have a TileMod\n", m_IndexPos.x, m_IndexPos.y);
		return;
	}
	else if (pTileMod != m_pTileMod)
	{
		std::cout << std::format("TileComp: Tried to unregister a TileMod ({}) on tile ({}, {}) that does not match the current TileMod ({})\n", typeid(*pTileMod).name(), m_IndexPos.x, m_IndexPos.y, typeid(*m_pTileMod).name());
		return;
	}
	m_pTileMod = nullptr;
}

bm::TileComp* bm::TileComp::GetUpTile() const
{
	return m_pUpTile;
}

bm::TileComp* bm::TileComp::GetRightTile() const
{
	return m_pRightTile;
}

bm::TileComp* bm::TileComp::GetDownTile() const
{
	return m_pDownTile;
}

bm::TileComp* bm::TileComp::GetLeftTile() const
{
	return m_pLeftTile;
}

void bm::TileComp::SetAdjescentTiles(TileComp* up, TileComp* right, TileComp* down, TileComp* left)
{
	m_pUpTile = up;
	m_pRightTile = right;
	m_pDownTile = down;
	m_pLeftTile = left;
}
