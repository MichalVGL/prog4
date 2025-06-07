#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "ISpawnSystem.h"


namespace bm
{
	class SpawnSystem final : public ISpawnSystem
	{
	public:

		void SpawnLevelStructures(int walls) override;

		dae::GameObjectHandle SpawnBomb(glm::vec2 pos) override;
		void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) override;
		void SpawnUpgrade(glm::vec2 pos, UpgradeType type);
	};
}

#endif // !SPAWNSYSTEM_H

