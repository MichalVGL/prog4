#ifndef BASETILE_H
#define BASETILE_H

#include <Texture.h>

namespace bm
{
	enum class BaseTileType
	{
		ground,
		wall,
		Count
	};

	class BaseTile final	//represents the basic info of a tile, TileComp composes this with other variables to make an instance
	{
	public:

		constexpr BaseTile(dae::TextureEntry textureEntry, bool walkable, bool allowSpawnables)
			: m_TextureEntry{ textureEntry }
			, m_Walkable{ walkable }
			, m_AllowSpawnables{ allowSpawnables }
		{
		}

		bool IsWalkable() const;
		bool AllowsSpawnables() const;
		dae::TextureEntry GetTextureEntry() const;

	private:

		const bool m_Walkable;
		const bool m_AllowSpawnables;
		const dae::TextureEntry m_TextureEntry;
	};
}

#endif // !BASETILE_H

