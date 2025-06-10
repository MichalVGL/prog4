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

		constexpr BaseTile(dae::TextureEntry textureEntry, bool walkable)
			: m_TextureEntry{ textureEntry }
			, m_Walkable{ walkable }
		{
		}

		bool IsWalkable() const;
		const dae::TextureEntry& GetTextureEntry() const;

	private:

		const bool m_Walkable;
		const dae::TextureEntry m_TextureEntry;
	};
}

#endif // !BASETILE_H

