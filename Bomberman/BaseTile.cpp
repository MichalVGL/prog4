#include "BaseTile.h"

bool bm::BaseTile::IsWalkable() const
{
	return m_Walkable;
}

dae::TextureEntry bm::BaseTile::GetTextureEntry() const
{
	return m_TextureEntry;
}