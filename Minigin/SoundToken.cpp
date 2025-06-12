#include "SoundToken.h"

#include <cassert>

#include "ServiceLocator.h"

dae::SoundToken::SoundToken(const SoundEntry& entry)
	:m_SoundEntry(entry)
{
	assert(m_pSoundSystem != nullptr && "Soundsystem in SoundToken should never be nullptr, this should be impossible due to Servicelocator returning a reference");
	m_pSoundSystem->RegisterSound(entry);
}

dae::SoundToken::~SoundToken()
{
	//if (m_pSoundSystem == &ServiceLocator::GetSoundSystem())	//is the soundsystem still the same when created?
	//{
	//	m_pSoundSystem->UnregisterSound(m_SoundEntry.id);
	//}
	Stop();
	m_pSoundSystem->UnregisterSound(m_SoundEntry.id);
}

void dae::SoundToken::Play(sound_volume volume, sound_loops loops)
{
	//if (m_pSoundSystem != &ServiceLocator::GetSoundSystem())	//is the soundsystem still the same when created?
	//{
	//	m_pSoundSystem = &ServiceLocator::GetSoundSystem();
	//	m_pSoundSystem->RegisterSound(m_SoundEntry);	// Reregister the entry (and load)
	//}
	m_pSoundSystem->PlayEffect(*this, volume, loops);
}

void dae::SoundToken::Stop()
{
	m_pSoundSystem->StopEffect(*this);
}

bool dae::SoundToken::IsPlaying() const
{
	return m_pSoundSystem->IsPlayingEffect(*this);
}

dae::sound_id dae::SoundToken::GetId() const
{
	return m_SoundEntry.id;
}

std::string_view dae::SoundToken::GetPath() const
{
	return m_SoundEntry.path;
}
