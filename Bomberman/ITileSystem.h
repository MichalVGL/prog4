#ifndef ITILESYSTEM_H
#define ITILESYSTEM_H

#include "TileComp.h"

namespace bm
{
	class ITileSystem
	{
	public:

		virtual ~ITileSystem() = default;

		virtual TileComp* GetTileFromWorldPos(glm::vec2 position) = 0;
		virtual TileComp* GetTileFromIndex(glm::ivec2 indexPos) = 0;

		virtual std::vector<TileComp*> GetAllTiles() = 0;
		virtual std::vector<TileComp*> GetAllWalkableTiles() = 0;
	};
}

#endif // !ITILESYSTEM_H
