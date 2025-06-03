#ifndef ITILEMOD_H
#define ITILEMOD_H

#include <sdbmHash.h>

namespace bm
{
	struct TileModId
	{
		template <size_t N>
		constexpr TileModId(const char(&name)[N])
			: id{ make_sdbm_hash(name) }
		{
		}

		unsigned int id;
	};

	// To implement if you want to modify a tile
	class ITileMod
	{
	public:

		virtual bool IsWalkable() const = 0;
		virtual bool AllowSpawnables() const = 0;
		virtual TileModId GetId() = 0;
	};
}

#endif // !ITILEMOD_H
