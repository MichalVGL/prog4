#include "SoundToken.h"

#include <cassert>

#include "ServiceLocator.h"

dae::SoundToken::SoundToken(const SoundEntry& entry)
	:m_SoundEntry(entry)
{
	assert(m_pInitSoundSystem != nullptr && "Soundsystem in SoundToken should never be nullptr, this should be impossible due to Servicelocator returning a reference");
	m_pInitSoundSystem->RegisterSound(entry);
}

dae::SoundToken::~SoundToken()
{
	if (m_pInitSoundSystem == &ServiceLocator::GetSoundSystem())	//is the soundsystem still the same when created?
	{
		m_pInitSoundSystem->UnregisterSound(m_SoundEntry.id);
	}
}

void dae::SoundToken::Play(sound_volume volume, sound_loops)	//todo add loops functionality
{
	if (m_pInitSoundSystem != &ServiceLocator::GetSoundSystem())	//is the soundsystem still the same when created?
	{
		m_pInitSoundSystem = &ServiceLocator::GetSoundSystem();
		m_pInitSoundSystem->RegisterSound(m_SoundEntry);	// Reregister the entry (and load)
	}
	m_pInitSoundSystem->PlayEffect(*this, volume);
}

dae::sound_effect_id dae::SoundToken::GetId() const
{
	return m_SoundEntry.id;
}

std::string_view dae::SoundToken::GetPath() const
{
	return m_SoundEntry.path;
}
