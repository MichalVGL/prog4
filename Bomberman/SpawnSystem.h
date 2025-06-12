#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "ISpawnSystem.h"


namespace bm
{
	class SpawnSystem final : public ISpawnSystem
	{
	public:

		void SpawnLevelWalls(int totalAmount, int powerUpWalls, std::vector<TileComp*> tileToIgnore) override;
		void SpawnEnemies(int amount, std::vector<EnemyType> types, std::vector<TileComp*> tileToIgnore) override;

		void SpawnPlayer() override;
		void SpawnEnemy(glm::vec2 pos, EnemyType type) override;
		void SpawnPlayerEnemy() override;

		void SpawnWall(glm::vec2 pos, ContainedObject containedObject = ContainedObject::none) override;
		dae::GameObjectHandle SpawnBomb(glm::vec2 pos) override;
		void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) override;
		void SpawnUpgrade(glm::vec2 pos, UpgradeType type);
		void SpawnRandomUpgrade(glm::vec2 pos);
		void SpawnDoor(glm::vec2 pos) override;

		void SpawnTempText(glm::vec2 pos, const std::string& text, float time, int size);
	};
}

#endif // !SPAWNSYSTEM_H

