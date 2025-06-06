#ifndef ISPAWNSYSTEM_H
#define ISPAWNSYSTEM_H

#include <Scene.h>

#include "BMUtils.h"

namespace bm
{
	class ISpawnSystem
	{
	public:
		virtual ~ISpawnSystem() = default;

		virtual void SpawnLevelStructures(int walls, dae::Scene& scene) = 0;	//spawns the amount of walls with 1 power up and a door

		virtual void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) = 0;
	};
}
#endif // !ISPAWNSYSTEM_H