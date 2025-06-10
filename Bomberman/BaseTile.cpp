#include "BaseTile.h"

bool bm::BaseTile::IsWalkable() const
{
	return m_Walkable;
}

const dae::TextureEntry& bm::BaseTile::GetTextureEntry() const
{
	return m_TextureEntry;
}