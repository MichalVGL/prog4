#ifndef PATHFINDERSYSTEM_H
#define PATHFINDERSYSTEM_H

#include "IPathfinderSystem.h"

namespace bm
{
	class PathfinderSystem final : public IPathfinderSystem
	{
	public:
		PathfinderSystem() = default;

		std::vector<glm::ivec2> FindPath(glm::vec2 beginPos, glm::vec2 targetPos) override;
		std::vector<glm::ivec2> GetRandomPath(glm::vec2 beginPos, int steps) override;
		void ConvertPathToDirections(std::vector<glm::ivec2>& path) override;
	};
}
#endif // !PATHFINDERSYSTEM_H
