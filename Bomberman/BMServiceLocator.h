#ifndef BMSERVICELOCATOR_H
#define BMSERVICELOCATOR_H

#include <memory>

#include "ITileSystem.h"
#include "IPathfinderSystem.h"
#include "ISpawnSystem.h"

namespace bm
{
	class BMServiceLocator
	{
	public:

		static void RegisterTileSystem(std::unique_ptr<ITileSystem>&& pTileSystem);
		static ITileSystem& GetTileSystem();

		static void RegisterPathfinderSystem(std::unique_ptr<IPathfinderSystem>&& pPathfinderSystem);
		static IPathfinderSystem& GetPathfinderSystem();

		static void RegisterSpawnSystem(std::unique_ptr<ISpawnSystem>&& pSpawnSystem);
		static ISpawnSystem& GetSpawnSystem();

	private:

		static std::unique_ptr<ITileSystem> s_pTileSystem;
		static std::unique_ptr<IPathfinderSystem> s_pPathfinderSystem;
		static std::unique_ptr<ISpawnSystem> s_pSpawnSystem;

	};
}

#endif // !BMSERVICELOCATOR_H
