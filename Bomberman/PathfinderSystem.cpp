#include "PathfinderSystem.h"

#include "BMServiceLocator.h"

#include <queue>
#include <unordered_map>
#include <vector>
#include <glm.hpp>
#include <set>
#include <algorithm>
#include <ServiceLocator.h>

std::vector<glm::ivec2> bm::PathfinderSystem::FindPath(glm::vec2 beginPos, glm::vec2 targetPos)
{
	//uses the Breadth-First Search algorithm to find the shortest path between two points on a grid of walkable tiles.

    auto& tileSystem = BMServiceLocator::GetTileSystem();

    auto* beginTile = tileSystem.GetTileFromWorldPos(beginPos);
    auto* targetTile = tileSystem.GetTileFromWorldPos(targetPos);

    if (!beginTile || !targetTile || !beginTile->IsWalkable() || !targetTile->IsWalkable())
        return {};

    std::queue<bm::TileComp*> openSet;
    std::unordered_map<bm::TileComp*, bm::TileComp*> cameFrom;
    std::unordered_map<bm::TileComp*, bool> visited;

    openSet.push(beginTile);
    visited[beginTile] = true;

    while (!openSet.empty())
    {
        bm::TileComp* current = openSet.front();
        openSet.pop();

        if (current == targetTile)  //path found
        {
            // Reconstruct path
            std::vector<glm::ivec2> path;
            bm::TileComp* n = current;
            while (n != nullptr)
            {
                path.push_back(n->GetIndexPosition());
				cameFrom.contains(n) ? n = cameFrom[n] : n = nullptr;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        bm::TileComp* neighbors[4] = {
            current->GetUpTile(),
            current->GetRightTile(),
            current->GetDownTile(),
            current->GetLeftTile()
        };

        for (bm::TileComp* neighbor : neighbors)
        {
            if (!neighbor || !neighbor->IsWalkable() || visited.contains(neighbor))
                continue;

            openSet.push(neighbor);
            visited[neighbor] = true;
            cameFrom[neighbor] = current;
        }
    }
    return std::vector<glm::ivec2>{};  //no path found
}

std::vector<glm::ivec2> bm::PathfinderSystem::GetRandomPath(glm::vec2 beginPos, int steps)
{
    auto& tileSystem = BMServiceLocator::GetTileSystem();
    auto* currentTile = tileSystem.GetTileFromWorldPos(beginPos);

    if (!currentTile || !currentTile->IsWalkable() || steps <= 0)
        return {};

    std::vector<glm::ivec2> path;
    std::set<bm::TileComp*> visited;
    path.push_back(currentTile->GetIndexPosition());
    visited.insert(currentTile);

    auto& randomSystem = dae::ServiceLocator::GetRandomSystem();

    for (int i = 0; i < steps; ++i)
    {
        std::vector<bm::TileComp*> neighbors;
        bm::TileComp* neighborTiles[4] = {
            currentTile->GetUpTile(),
            currentTile->GetRightTile(),
            currentTile->GetDownTile(),
            currentTile->GetLeftTile()
        };

        for (bm::TileComp* neighbor : neighborTiles)
        {
            if (neighbor && neighbor->IsWalkable() && !visited.contains(neighbor))
                neighbors.push_back(neighbor);
        }

        if (neighbors.empty())
            break; // No more moves possible

        int idx = randomSystem.GetRandomInt(0, static_cast<int>(neighbors.size()) - 1);
        currentTile = neighbors[idx];
        path.push_back(currentTile->GetIndexPosition());
        visited.insert(currentTile);
    }

    return path;
}

void bm::PathfinderSystem::ConvertPathToDirections(std::vector<glm::ivec2>& path)
{
	if (path.empty())
		return;
	std::vector<glm::ivec2> directions;
	glm::ivec2 previous = path.back();
	path.pop_back();
	while (!path.empty())
	{
		glm::ivec2 current = path.back();
		path.pop_back();
		glm::ivec2 direction = previous - current;
		if (direction != glm::ivec2(0, 0)) // Only add non-zero directions
			directions.push_back(direction);
		previous = current;
	}
	path = std::move(directions);
}
