#include "TileSystem.h"

#include <algorithm>
#include <fstream>
#include <filesystem>
#include <DaeFiles.h>

#include "ObjectConstructions.h"

//================================================================================================
// Level_TileSystem
//================================================================================================

//flyweight data
const std::array<bm::BaseTile, static_cast<int>(bm::BaseTileType::Count)> bm::Level_TileSystem::s_BaseTileTypes{
		bm::BaseTile{ dae::TextureEntry{ "EmptyTile.png" }, true },			//Ground
		bm::BaseTile{ dae::TextureEntry{ "IndestructableWall.png" }, false }	//Wall
};

bm::Level_TileSystem::Level_TileSystem(dae::Scene& scene)
{
	auto parentGObj = scene.Add(GOBJ("Level"));	//parent of all tiles

	//todo, load tiletypes from a file
	auto tileTypes = LoadTilesFromFile(s_BaseLevelFile);

	for (size_t i{ 0 }; i < m_Tiles.size(); ++i)
	{
		auto go{ RenderGOBJ("LevelTile") };
		m_Tiles[i] = go->AddComponent<TileComp>(&s_BaseTileTypes.at(static_cast<int>(tileTypes.at(i))), glm::ivec2{i % LEVELTILE_COLS, i / LEVELTILE_COLS});
		go->SetParent(parentGObj);
		scene.Add(std::move(go));
	}

	//Setup the adjescent tiles
	for (size_t i{ 0 }; i < m_Tiles.size(); ++i)
	{
		auto& tile = m_Tiles[i];
		glm::ivec2 indexPos{ i % LEVELTILE_COLS, i / LEVELTILE_COLS };
		tile->SetAdjescentTiles(
			GetTileFromIndex(glm::ivec2{ indexPos.x, indexPos.y + 1 }),	//Up
			GetTileFromIndex(glm::ivec2{ indexPos.x + 1, indexPos.y }),	//Right
			GetTileFromIndex(glm::ivec2{ indexPos.x, indexPos.y - 1 }),	//Down
			GetTileFromIndex(glm::ivec2{ indexPos.x - 1, indexPos.y })	//Left
		);
	}
}

bm::TileComp* bm::Level_TileSystem::GetTileFromWorldPos(glm::vec2 position)
{
	auto tilePos = GetTilePosition(position);	

	return GetTileFromIndex(tilePos);
}

bm::TileComp* bm::Level_TileSystem::GetTileFromIndex(glm::ivec2 indexPos)
{
	if ((indexPos.x < 0 || indexPos.x >= LEVELTILE_COLS || indexPos.y < 0 || indexPos.y >= LEVELTILE_ROWS)
		== false)	//Is inside the bounds?
	{
		return m_Tiles[indexPos.y * LEVELTILE_COLS + indexPos.x];	//Get the tile from the array
	}
	return nullptr;
}

//============HELPERS=================================

glm::ivec2 bm::Level_TileSystem::GetTilePosition(glm::vec2 position) const
{
	//convert a world position to the tile it represents (does not validate the tile!!!)
	return glm::ivec2{ static_cast<int>(position.x / TILE_SIZE), static_cast<int>(position.y / TILE_SIZE) };	
}

std::vector<bm::BaseTileType> bm::Level_TileSystem::LoadTilesFromFile(std::string_view file)
{
	std::filesystem::path path{ dae::dataPath };
	path /= file;	//append the file path to the data path

	//check if the file exists
	if (!std::filesystem::exists(path))
	{
		//std::cout << "Current working directory: " << std::filesystem::current_path() << '\n';
		std::cout << std::format("Couldn't load level from file {}, file doesn't exist.\n", file);
		throw std::runtime_error("File does not exist: " + std::string(file));
	}

	// Open a binary file for reading
	std::ifstream inFile(path, std::ios::binary);
	if (!inFile)
	{
		std::cout << std::format("Unknown error loading level file. [{}]\n", file);
		throw std::runtime_error("Could not open file for reading.");
	}
	// Read the number of tiles
	std::vector<BaseTileType> tiles{};
	size_t size{};
	inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	if (size != m_Tiles.size())
	{
		std::cout << std::format("File {} doesn't contain the correct amount of tiles. Expected: {}, Found: {}\n", file, m_Tiles.size(), size);
		throw std::runtime_error("File doesn't contain the correct amount of tiles.");
	}
	tiles.resize(size);
	// Read the tile data
	for (size_t i = 0; i < size; ++i)
	{
		BaseTileType tile;
		inFile.read(reinterpret_cast<char*>(&tile), sizeof(tile));
		if (tile < BaseTileType::ground || tile > BaseTileType::wall)
		{
			std::cout << std::format("Invalid tile type {} encountered in file {}.\n", static_cast<int>(tile), file);
			throw std::runtime_error("Invalid tile type encountered.");
		}
		tiles[i] = tile;
	}
	inFile.close();
	return tiles;
}
