#include "BMServiceLocator.h"

#include <cassert>

#include "TileSystem.h"
#include "PathfinderSystem.h"
#include "SpawnSystem.h"
#include "UpgradeSystem.h"

std::unique_ptr<bm::ITileSystem> bm::BMServiceLocator::s_pTileSystem{ std::make_unique<bm::Null_TileSystem>() };
std::unique_ptr<bm::IPathfinderSystem> bm::BMServiceLocator::s_pPathfinderSystem{ std::make_unique<bm::PathfinderSystem>() };
std::unique_ptr<bm::ISpawnSystem> bm::BMServiceLocator::s_pSpawnSystem{ std::make_unique<bm::SpawnSystem>() };
std::unique_ptr<bm::IUpgradeSystem> bm::BMServiceLocator::s_pUpgradeSystem{ std::make_unique<bm::UpgradeSystem>() };

void bm::BMServiceLocator::RegisterTileSystem(std::unique_ptr<ITileSystem>&& pTileSystem)
{
	assert(pTileSystem != nullptr && "BMServiceLocator::RegisterTileSystem: Tried to register nullptr as TileSystem");
	s_pTileSystem = std::move(pTileSystem);
}

bm::ITileSystem& bm::BMServiceLocator::GetTileSystem()
{
	if (!s_pTileSystem)
	{
		s_pTileSystem = std::make_unique<Null_TileSystem>();
	}
	return *s_pTileSystem;
}

void bm::BMServiceLocator::RegisterPathfinderSystem(std::unique_ptr<IPathfinderSystem>&& pPathfinderSystem)
{
	assert(pPathfinderSystem != nullptr && "BMServiceLocator::RegisterPathfinderSystem: Tried to register nullptr as PathfinderSystem");
	s_pPathfinderSystem = std::move(pPathfinderSystem);
}

bm::IPathfinderSystem& bm::BMServiceLocator::GetPathfinderSystem()
{
	if (!s_pPathfinderSystem)
	{
		s_pPathfinderSystem = std::make_unique<bm::PathfinderSystem>();
	}
	return *s_pPathfinderSystem;
}

void bm::BMServiceLocator::RegisterSpawnSystem(std::unique_ptr<ISpawnSystem>&& pSpawnSystem)
{
	assert(pSpawnSystem != nullptr && "BMServiceLocator::RegisterSpawnSystem: Tried to register nullptr as SpawnSystem");
	s_pSpawnSystem = std::move(pSpawnSystem);
}

bm::ISpawnSystem& bm::BMServiceLocator::GetSpawnSystem()
{
	if (!s_pSpawnSystem)
	{
		s_pSpawnSystem = std::make_unique<bm::SpawnSystem>();
	}
	return *s_pSpawnSystem;
}

void bm::BMServiceLocator::RegisterUpgradeSystem(std::unique_ptr<IUpgradeSystem>&& pUpgradeSystem)
{
	assert(pUpgradeSystem != nullptr && "BMServiceLocator::RegisterUpgradeSystem: Tried to register nullptr as UpgradeSystem");
	s_pUpgradeSystem = std::move(pUpgradeSystem);
}

bm::IUpgradeSystem& bm::BMServiceLocator::GetUpgradeSystem()
{
	if (!s_pUpgradeSystem)
	{
		s_pUpgradeSystem = std::make_unique<bm::UpgradeSystem>();
	}
	return *s_pUpgradeSystem;
}
