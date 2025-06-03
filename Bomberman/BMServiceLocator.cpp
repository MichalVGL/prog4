#include "BMServiceLocator.h"

#include <cassert>

#include "TileSystem.h"

std::unique_ptr<bm::ITileSystem> bm::BMServiceLocator::s_pTileSystem{ std::make_unique<bm::Null_TileSystem>() };

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
