#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "ISpawnSystem.h"

namespace bm
{
	class SpawnSystem final : public ISpawnSystem
	{
	public:

		void SpawnLevelStructures(int walls, dae::Scene& scene) override;

	};
}

#endif // !SPAWNSYSTEM_H

