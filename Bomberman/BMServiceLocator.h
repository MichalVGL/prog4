#ifndef BMSERVICELOCATOR_H
#define BMSERVICELOCATOR_H

#include <memory>

#include "ITileSystem.h"
#include "IPathfinderSystem.h"
#include "ISpawnSystem.h"
#include "IUpgradeSystem.h"
#include "IScoreSystem.h"

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

		static void RegisterUpgradeSystem(std::unique_ptr<IUpgradeSystem>&& pUpgradeSystem);
		static IUpgradeSystem& GetUpgradeSystem();

		static void RegisterScoreSystem(std::unique_ptr<IScoreSystem>&& pScoreSystem);
		static IScoreSystem& GetScoreSystem();

	private:

		static std::unique_ptr<ITileSystem> s_pTileSystem;
		static std::unique_ptr<IPathfinderSystem> s_pPathfinderSystem;
		static std::unique_ptr<ISpawnSystem> s_pSpawnSystem;
		static std::unique_ptr<IUpgradeSystem> s_pUpgradeSystem;
		static std::unique_ptr<IScoreSystem> s_pScoreSystem;

	};
}

#endif // !BMSERVICELOCATOR_H
