#ifndef ISPAWNSYSTEM_H
#define ISPAWNSYSTEM_H

#include <Scene.h>

namespace bm
{
	class ISpawnSystem
	{
	public:
		virtual ~ISpawnSystem() = default;

		virtual void SpawnLevelStructures(int walls, dae::Scene& scene) = 0;	//spawns the amount of walls with 1 power up and a door
	};
}
#endif // !ISPAWNSYSTEM_H