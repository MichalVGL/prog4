#ifndef ITILEMOD_H
#define ITILEMOD_H

#include <sdbmHash.h>

namespace dae
{
	class GameObject;
}

namespace bm
{
	struct TileModId
	{
		template <size_t N>
		constexpr TileModId(const char(&name)[N])
			: id{ dae::make_sdbm_hash(name) }
		{
		}

		unsigned int id;
	};

	// To implement if you want to modify a tile
	class TileMod
	{
	public:

		TileMod(TileModId id, dae::GameObject& object);	//auto register to the tile

		virtual bool IsWalkable() const = 0;
		TileModId GetId() const;

		void Unregister();

	private:

		TileModId m_Id;
		dae::GameObject& m_Object;	//the object that has this tile mod
		
	};
}

#endif // !ITILEMOD_H