#ifndef IPATHFINDERSYSTEM_H
#define IPATHFINDERSYSTEM_H

#include <vector>
#include <glm.hpp>

namespace bm
{
	class IPathfinderSystem
	{
	public:
		virtual ~IPathfinderSystem() = default;

		virtual std::vector<glm::ivec2> FindPath(glm::vec2 beginPos, glm::vec2 targetPos) = 0;	
		virtual std::vector<glm::ivec2> GetRandomPath(glm::vec2 beginPos, int steps) = 0;		
		virtual void ConvertPathToDirections(std::vector<glm::ivec2>& path) = 0;	//converts a path to directions and reverses the vector (use .pop() to get the next direction)
	};
}
#endif // !IPATHFINDERSYSTEM_H