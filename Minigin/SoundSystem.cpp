#include "SoundSystem.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <filesystem>
#include <cassert>

#include "SoundToken.h"

//===================================================================================================================================================
//SDL_SoundSystem
//===================================================================================================================================================

dae::SDL_SoundSystem::SDL_SoundSystem(std::filesystem::path dataPath)
	: m_DataPath{ dataPath }
{
	// Initialize SDL audio subsystem
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL audio could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error("SDL audio could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL mixer could not initialize! SDLMix_Error: " << Mix_GetError() << std::endl;
		throw std::runtime_error("SDL mixer could not initialize! SDLMix_Error: " + std::string(Mix_GetError()));
	}

	m_SDLThread = std::jthread([this](std::stop_token stopToken) { SoundThread(stopToken); }); //In body of the constructor to ensure that all the data is initialized before the thread starts
}

dae::SDL_SoundSystem::~SDL_SoundSystem()
{
	//notify thread to stop
	m_SDLThread.request_stop();
	m_CV.notify_all();

	// Clean up SDL_mixer
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void dae::SDL_SoundSystem::SetGlobalVolume(sound_volume volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	m_GlobalVolume = volume;
}

void dae::SDL_SoundSystem::PlayEffect(const SoundToken& soundToken, sound_volume volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	std::lock_guard<std::mutex> lock(m_Mtx);
	m_SoundPlayQueue.push(std::make_pair(soundToken.GetId(), volume * m_GlobalVolume));
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::RegisterSound(const SoundEntry& soundEntry)
{
	std::lock_guard<std::mutex> lock(m_Mtx);
	m_SoundLoadQueue.push(soundEntry);
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::UnregisterSound(sound_effect_id id)
{
	std::lock_guard<std::mutex> lock(m_Mtx);
	m_SoundUnloadQueue.push(id);
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::SoundThread(std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> lock(m_Mtx);

		m_CV.wait(lock, [&]() {
			return m_SoundPlayQueue.size() != 0 or m_SoundLoadQueue.size() != 0 or m_SoundUnloadQueue.size() != 0
				or stopToken.stop_requested(); });

		if (stopToken.stop_requested())
			break;

		if (m_SoundLoadQueue.size() != 0)	//load sound (priority)
		{
			auto soundEntry = m_SoundLoadQueue.front();
			m_SoundLoadQueue.pop();
			lock.unlock();

			auto loc = m_Sounds.find(soundEntry.id);
			if (loc == m_Sounds.end())
			{
				std::string path = m_DataPath.string();
				path += soundEntry.path;
				auto [newLoc, succes] = m_Sounds.emplace(soundEntry.id, SoundResource(path));
				if (!succes)
				{
					std::cout << std::format("Failed to insert sound effect into map. (id: {}, path: {}\n)", soundEntry.id, path);
					continue;
				}
				loc = newLoc;
				loc->second.pSoundEffect->Load();
			}
			loc->second.tokenAmount++;
		}
		else if (m_SoundUnloadQueue.size() != 0)	//unload sound
		{
			auto soundId = m_SoundUnloadQueue.front();
			m_SoundUnloadQueue.pop();
			lock.unlock();

			auto loc = m_Sounds.find(soundId);
			if (loc == m_Sounds.end())
			{
				std::cout << std::format("Failed to find sound effect to unload with id: {}\n", soundId);
				continue;
			}

			loc->second.tokenAmount--;
			if (loc->second.tokenAmount <= 0)
			{
				m_Sounds.erase(loc);
			}
		}
		else //play sound
		{
			auto [soundId, volume] = m_SoundPlayQueue.front();
			m_SoundPlayQueue.pop();
			lock.unlock();

			auto loc = m_Sounds.find(soundId);
			if (loc == m_Sounds.end())
			{
				std::cout << std::format("Failed to find sound effect to play with id: {}\n", soundId);
				continue;
			}

			auto& audioEffect = *(loc->second.pSoundEffect);
			audioEffect.SetVolume(volume);
			audioEffect.PlayEffect(0);
		}
	}
}

//===================================================================================================================================================
//Logger_SoundSystem
//===================================================================================================================================================

dae::Logger_SoundSystem::Logger_SoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:m_pSoundSystem{ std::move(soundSystem) }
{
}

void dae::Logger_SoundSystem::SetGlobalVolume(sound_volume volume)
{
	std::cout << std::format("Setting global volume to: {}\n", volume);
	m_pSoundSystem->SetGlobalVolume(volume);
}

void dae::Logger_SoundSystem::PlayEffect(const SoundToken& soundToken, sound_volume volume)
{
	std::cout << std::format("Playing sound effect with id: {}\n", soundToken.GetId());
	m_pSoundSystem->PlayEffect(soundToken, volume);
}

void dae::Logger_SoundSystem::RegisterSound(const SoundEntry& soundEntry)
{
	std::cout << std::format("Registering sound effect\n\t\"{}\"\tid: {}\n", soundEntry.path, soundEntry.id);
	m_pSoundSystem->RegisterSound(soundEntry);
}

void dae::Logger_SoundSystem::UnregisterSound(sound_effect_id id)
{
	std::cout << std::format("Unregistering sound effect with id: {}\n", id);
	m_pSoundSystem->UnregisterSound(id);
}
