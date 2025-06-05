#include "LevelComp.h"

#include <algorithm>

#include "TileComp.h"
#include "ObjectConstructions.h"

bm::LevelComp::LevelComp(dae::GameObject& parent)
	:Component(parent)
{
	//create a "2D" grid of tiles and set the pointers of the array to them
	for (size_t i{ 0 }; i < m_Tiles.size(); ++i)
	{
		auto go{ RenderGOBJ("LevelTile") };
		m_Tiles[i] = go->AddComponent<TileComp>(TileType::wall, glm::ivec2{ i % LEVELTILE_COLS, i / LEVELTILE_COLS });
		go->SetParent(&GetOwner());
		GetOwner().GetScene().Add(std::move(go));
	}
}