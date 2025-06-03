#ifndef BMSERVICELOCATOR_H
#define BMSERVICELOCATOR_H

#include <memory>

#include "ITileSystem.h"

namespace bm
{
	class BMServiceLocator
	{
	public:

		static void RegisterTileSystem(std::unique_ptr<ITileSystem>&& pTileSystem);
		static ITileSystem& GetTileSystem();

	private:

		static std::unique_ptr<ITileSystem> s_pTileSystem;

	};
}

#endif // !BMSERVICELOCATOR_H
