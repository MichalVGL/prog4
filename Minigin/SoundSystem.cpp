#include "SoundSystem.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <filesystem>
#include <cassert>

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
	m_SDLThread.request_stop();
	m_CV.notify_all(); 

	// Clean up SDL_mixer
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void dae::SDL_SoundSystem::PlayEffect(const SoundEntry& soundEntry, sound_volume volume)
{
	std::lock_guard<std::mutex> lock(m_Mtx);
	m_SoundQueue.push(std::make_pair(soundEntry, volume));
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::SoundThread(std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> lock(m_Mtx);

		m_CV.wait(lock, [&]() {
			return m_SoundQueue.size() != 0 or stopToken.stop_requested(); });

		if (stopToken.stop_requested())
			break;

		auto [soundEntry, volume] = m_SoundQueue.front();
		m_SoundQueue.pop();
		lock.unlock();

		//find/insert the sound effect
		auto loc = m_SoundEffects.find(soundEntry.id);
		if (loc == m_SoundEffects.end())
		{
			std::string path = m_DataPath.string();
			path += soundEntry.path;
			auto [newLoc, succes] = m_SoundEffects.emplace(soundEntry.id, SoundEffect(path));

			if (!succes)
			{
				std::cout << "Failed to insert sound effect into map" << std::endl;
				continue;
			}
			loc = newLoc;
		}

		//load and play the sound effect
		auto& audioEffect = loc->second;
		if (!audioEffect.IsLoaded())
		{
			audioEffect.Load();
		}
		audioEffect.SetVolume(volume);
		audioEffect.PlayEffect(0);
	}
}

//===================================================================================================================================================
//Logger_SoundSystem
//===================================================================================================================================================

dae::Logger_SoundSystem::Logger_SoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:m_pSoundSystem{ std::move(soundSystem) }
{
}

void dae::Logger_SoundSystem::PlayEffect(const SoundEntry& soundEntry, sound_volume volume)
{
	m_pSoundSystem->PlayEffect(soundEntry, volume);

	//todo prevent cout from having unpredictable output due to threading, (maybe seperate namespace for "global" locks for cout?)
	std::cout << std::format("Playing sound effect: {} (id: {})", soundEntry.path, soundEntry.id) << std::endl;	
}
