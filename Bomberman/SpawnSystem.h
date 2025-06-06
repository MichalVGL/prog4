#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "ISpawnSystem.h"


namespace bm
{
	class SpawnSystem final : public ISpawnSystem
	{
	public:

		void SpawnLevelStructures(int walls, dae::Scene& scene) override;

		
		void SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount) override;

	};
}

#endif // !SPAWNSYSTEM_H

