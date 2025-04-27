#ifndef SERVICELOCATOR_H  
#define SERVICELOCATOR_H  

#include <memory>  

#include "ISoundSystem.h"  

namespace dae
{
	class ServiceLocator final
	{
	public:

		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem);
		static ISoundSystem& GetSoundSystem();

	private:

		static std::unique_ptr<ISoundSystem> m_pSoundSystem;
	};
}

#endif // !SERVICELOCATOR_H
