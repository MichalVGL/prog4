#ifndef ISPAWNSYSTEM_H
#define ISPAWNSYSTEM_H

#include <Scene.h>

#include "BMUtils.h"
#include "UpgradeComp.h"

namespace bm
{
	class ISpawnSystem
	{
	public:
		virtual ~ISpawnSystem() = default;

		virtual void SpawnLevelStructures(int walls) = 0;

		virtual dae::GameObjectHandle SpawnBomb(glm::vec2 pos) = 0;
		virtual void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) = 0;
		virtual void SpawnUpgrade(glm::vec2 pos, UpgradeType type) = 0;
	};
}
#endif // !ISPAWNSYSTEM_H