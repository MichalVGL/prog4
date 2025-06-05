#ifndef TILESYSTEM_H
#define TILESYSTEM_H

#include "ITileSystem.h"

#include <array>

#include "BMGameDefines.h"
#include "BaseTile.h"

class dae::Scene;

namespace bm
{
	class Null_TileSystem final : public ITileSystem
	{
		TileComp* GetTileFromWorldPos(glm::vec2) override { return nullptr; };
		TileComp* GetTileFromIndex(glm::ivec2) override { return nullptr; };
	};

	class Level_TileSystem final : public ITileSystem
	{
	public:

		Level_TileSystem(dae::Scene& scene);

		TileComp* GetTileFromWorldPos(glm::vec2 position) override;
		TileComp* GetTileFromIndex(glm::ivec2 indexPos) override;

	private:

		glm::ivec2 GetTilePosition(glm::vec2 position) const;	//Get tile position from a world position
		std::vector<BaseTileType> LoadTilesFromFile(std::string_view filePath);	//Load the tiles from a file

		std::array<TileComp*, LEVELTILES_TOTAL> m_Tiles{};

		const static std::array<BaseTile, static_cast<int>(BaseTileType::Count)> s_BaseTileTypes;
		constexpr static std::string_view s_BaseLevelFile{"Levels/main.bmlevel"};

	};
}

#endif // !TILESYSTEM_H

