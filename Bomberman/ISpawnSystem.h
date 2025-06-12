#ifndef ISPAWNSYSTEM_H
#define ISPAWNSYSTEM_H

#include <Scene.h>

#include "BMUtils.h"
#include "UpgradeComp.h"
#include "TileComp.h"
#include "WallComp.h"
#include "EnemyTypes.h"

namespace bm
{
	class ISpawnSystem
	{
	public:
		virtual ~ISpawnSystem() = default;

		virtual void SpawnLevelWalls(int totalAmount, int powerUpWalls, std::vector<TileComp*> tileToIgnore) = 0;
		virtual void SpawnEnemies(int amount, std::vector<EnemyType> types, std::vector<TileComp*> tileToIgnore) = 0;

		virtual void SpawnPlayer() = 0;
		virtual void SpawnEnemy(glm::vec2 pos, EnemyType type) = 0;
		virtual void SpawnPlayerEnemy() = 0;

		virtual void SpawnWall(glm::vec2 pos, ContainedObject containedObject = ContainedObject::none) = 0;
		virtual dae::GameObjectHandle SpawnBomb(glm::vec2 pos) = 0;
		virtual void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) = 0;
		virtual void SpawnUpgrade(glm::vec2 pos, UpgradeType type) = 0;
		virtual void SpawnRandomUpgrade(glm::vec2 pos) = 0;
		virtual void SpawnDoor(glm::vec2 pos) = 0;

		virtual void SpawnTempText(glm::vec2 pos, const std::string& text, float time, int size) = 0;
	};
}
#endif // !ISPAWNSYSTEM_H