#include "ServiceLocator.h"

#include <cassert>

#include "SoundSystem.h"

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_pSoundSystem{ std::make_unique<dae::Null_SoundSystem>() };

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem)
{
	assert(pSoundSystem != nullptr && "ServiceLocator::RegisterSoundSystem: Tried to register nullptr as SoundSystem");
	m_pSoundSystem = std::move(pSoundSystem);
}

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	if (!m_pSoundSystem)
	{
		m_pSoundSystem = std::make_unique<dae::Null_SoundSystem>();
	}
	return *m_pSoundSystem;
}
 