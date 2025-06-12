#include "SoundEffect.h"  
#include <SDL.h>  
#include <SDL_mixer.h>  
#include <functional>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <format>

template <>
struct std::default_delete<Mix_Chunk>
{
	void operator()(Mix_Chunk* p) const
	{
		Mix_FreeChunk(p);
	}
};

class dae::SoundEffect::SDL_SoundEffectImpl final {

public:

	SDL_SoundEffectImpl(const std::string& path);

	SDL_SoundEffectImpl() = delete;

	void Load();
	bool IsLoaded() const;

	void SetVolume(sound_volume volume = 1.f);

	int PlayEffect(int loops);
	void StopEffect();
	bool IsPlaying() const;

private:

	std::string m_Path;

	std::unique_ptr<Mix_Chunk> m_pChunk{ nullptr };
	int m_Channel{ -1 };
};

dae::SoundEffect::SDL_SoundEffectImpl::SDL_SoundEffectImpl(const std::string& path)
	:m_Path{ path }
{
}

void dae::SoundEffect::SDL_SoundEffectImpl::Load()
{
	if (!m_pChunk)
	{
		m_pChunk.reset(Mix_LoadWAV(m_Path.c_str()));
		if (!m_pChunk)
		{
			std::cout << std::format("Failed to load sound effect! SDL_mixer Error: {}\n", Mix_GetError());
		}
		SetVolume();
	}
}

bool dae::SoundEffect::SDL_SoundEffectImpl::IsLoaded() const
{
	return m_pChunk != nullptr;
}

void dae::SoundEffect::SDL_SoundEffectImpl::SetVolume(sound_volume volume)
{
	if (m_pChunk)
	{
		volume = std::clamp(volume, 0.0f, 1.0f);
		Mix_VolumeChunk(m_pChunk.get(), static_cast<int>(volume * MIX_MAX_VOLUME));
	}
}

int dae::SoundEffect::SDL_SoundEffectImpl::PlayEffect(int loops)
{
	if (m_pChunk)
	{
		m_Channel = Mix_PlayChannel(-1, m_pChunk.get(), loops);
		if (m_Channel == -1)
		{
			std::cout << std::format("Failed to play sound effect! SDL_mixer Error: {}\n", Mix_GetError());
		}
	}
	return m_Channel;
}

void dae::SoundEffect::SDL_SoundEffectImpl::StopEffect()
{
	if (m_Channel != -1)
	{
		if (Mix_Playing(m_Channel) == 1)	//currently playing the sound
		{
			Mix_HaltChannel(m_Channel);
		}
		m_Channel = -1;	//reset channel
	}
}

bool dae::SoundEffect::SDL_SoundEffectImpl::IsPlaying() const
{
	return m_Channel != -1 && Mix_Playing(m_Channel) != 0;
}

//===================================================================================================================================================  
//SoundEffect  
//===================================================================================================================================================  

dae::SoundEffect::SoundEffect(const std::string& path)
	:m_pSDLSoundEffectImpl{ std::make_unique<SDL_SoundEffectImpl>(path) }
{
}

//to make pimpl work with a unique_ptr
dae::SoundEffect::~SoundEffect() = default;
dae::SoundEffect::SoundEffect(SoundEffect&&) noexcept = default;
dae::SoundEffect& dae::SoundEffect::operator=(SoundEffect&&) noexcept = default;

void dae::SoundEffect::Load()
{
	m_pSDLSoundEffectImpl->Load();
}

bool dae::SoundEffect::IsLoaded() const
{
	return m_pSDLSoundEffectImpl->IsLoaded();
}

void dae::SoundEffect::SetVolume(sound_volume volume)
{
	m_pSDLSoundEffectImpl->SetVolume(volume);
}

int dae::SoundEffect::PlayEffect(int loops)
{
	return m_pSDLSoundEffectImpl->PlayEffect(loops);
}

void dae::SoundEffect::StopEffect()
{
	m_pSDLSoundEffectImpl->StopEffect();
}

bool dae::SoundEffect::IsPlaying() const
{
	return m_pSDLSoundEffectImpl->IsPlaying();
}
