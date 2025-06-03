#include "BaseTile.h"

bool bm::BaseTile::IsWalkable() const
{
	return m_Walkable;
}

bool bm::BaseTile::AllowsSpawnables() const
{
	return m_AllowSpawnables;
}

dae::TextureEntry bm::BaseTile::GetTextureEntry() const
{
	return m_TextureEntry;
}