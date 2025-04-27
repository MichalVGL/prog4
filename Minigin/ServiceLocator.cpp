#include "ServiceLocator.h"

#include <cassert>

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_pSoundSystem{ nullptr };

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem)
{
	m_pSoundSystem = std::move(pSoundSystem);
}

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	assert(m_pSoundSystem != nullptr && "ServiceLocator::GetSoundSystem: SoundSystem not registered");
	return *m_pSoundSystem;
}
