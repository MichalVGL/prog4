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
		unsigned int id;

		template <size_t N>
		constexpr TileModId(const char(&name)[N])
			: id{ dae::make_sdbm_hash(name) }
		{
		}

		//== operator
		bool operator==(const TileModId& other) const
		{
			return id == other.id;
		}
	};

	// To implement if you want to modify a tile
	class TileMod
	{
	public:

		TileMod(dae::GameObject& object, TileModId id);	//auto register to the tile, make sure to set position before add the component that implements this

		~TileMod() = default;
		TileMod(const TileMod&) = delete;
		TileMod(TileMod&&) noexcept = delete;
		TileMod& operator=(const TileMod&) = delete;
		TileMod& operator=(TileMod&&) noexcept = delete;

		virtual bool IsWalkable() const = 0;
		TileModId GetId() const;

		void Unregister();

	private:

		TileModId m_Id;
		dae::GameObject& m_Object;	//the object that has this tile mod
		bool m_Registered{ false };
		
	};
}

#endif // !ITILEMOD_H