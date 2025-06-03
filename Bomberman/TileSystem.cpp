#include "TileSystem.h"

#include <algorithm>

#include "ObjectConstructions.h"

//================================================================================================
// Level_TileSystem
//================================================================================================

//flyweight data
const std::array<bm::BaseTile, static_cast<int>(bm::BaseTileType::Count)> bm::Level_TileSystem::m_BaseTileTypes{
		bm::BaseTile{ dae::TextureEntry{ "EmptyTile.png" }, true, true },			//Ground
		bm::BaseTile{ dae::TextureEntry{ "IndestructableWall.png" }, false, false }	//Wall
};

bm::Level_TileSystem::Level_TileSystem(dae::Scene& scene)
{
	auto parentGObj = scene.Add(GOBJ("Level"));	//parent of all tiles

	//todo, load tiletypes from a file

	for (size_t i{ 0 }; i < m_Tiles.size(); ++i)
	{
		auto go{ RenderGOBJ("LevelTile") };
		m_Tiles[i] = go->AddComponent<TileComp>(&m_BaseTileTypes.at(static_cast<int>(bm::BaseTileType::Ground)), glm::ivec2{i % LEVELTILE_COLS, i / LEVELTILE_COLS});
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
