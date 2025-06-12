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
	if ((SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO) == false)
	{
		std::cout << "SDL audio was not initialized! Initialize SDL_INIT_AUDIO before creating SDL_Soundsystem\n";
		throw std::runtime_error("SDL audio was not initialized! Initialize SDL_INIT_AUDIO before creating SDL_Soundsystem");
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << std::format("SDL mixer could not initialize! SDLMix_Error: {}\n", Mix_GetError());
		throw std::runtime_error("SDL mixer could not initialize! SDLMix_Error: " + std::string(Mix_GetError()));
	}

	m_SDLThread = std::jthread([this](std::stop_token stopToken) { SoundThread(stopToken); }); //In body of the constructor to ensure that all the data is initialized before the thread starts
}

void dae::SDL_SoundSystem::Quit()
{
	m_SDLThread.request_stop();
	m_CV.notify_all();

	std::lock_guard<std::mutex> lock(m_QueueMtx);
	m_Sounds.clear();

	Mix_CloseAudio();
}

void dae::SDL_SoundSystem::SetGlobalVolume(sound_volume volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	m_GlobalVolume = volume;
}

void dae::SDL_SoundSystem::PlayEffect(const SoundToken& soundToken, sound_volume volume, sound_loops loops)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	std::lock_guard<std::mutex> lock(m_QueueMtx);
	m_SoundPlayQueue.push(std::make_tuple(soundToken.GetId(), volume * m_GlobalVolume, loops));
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::StopEffect(const SoundToken& soundToken)
{
	std::lock_guard<std::mutex> lock(m_QueueMtx);
	m_SoundStopQueue.push(soundToken.GetId());
	m_CV.notify_one();
}

bool dae::SDL_SoundSystem::IsPlayingEffect(const SoundToken& soundToken) const
{
	auto soundId = soundToken.GetId();

	std::lock_guard<std::mutex> lock(m_SoundsMtx);

	auto loc = m_Sounds.find(soundId);
	if (loc == m_Sounds.end())
	{
		std::cout << std::format("Failed to find sound effect to check with id: {}\n", soundId);
		return false;
	}

	auto& audioEffect = *(loc->second.pSoundEffect);
	return audioEffect.IsPlaying();
}

void dae::SDL_SoundSystem::RegisterSound(const SoundEntry& soundEntry)
{
	std::lock_guard<std::mutex> lock(m_QueueMtx);
	m_SoundLoadQueue.push(soundEntry);
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::UnregisterSound(sound_id id)
{
	std::lock_guard<std::mutex> lock(m_QueueMtx);
	m_SoundUnloadQueue.push(id);
	m_CV.notify_one();
}

void dae::SDL_SoundSystem::SoundThread(std::stop_token stopToken)
{
	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> lock(m_QueueMtx);

		m_CV.wait(lock, [&]() {
			return m_SoundPlayQueue.size() != 0 or m_SoundLoadQueue.size() != 0 or m_SoundUnloadQueue.size() != 0 or m_SoundStopQueue.size() != 0
				or stopToken.stop_requested(); });

		if (stopToken.stop_requested())
			break;

		if (m_SoundStopQueue.size() != 0)	//stop sound (priority)
		{
			auto soundId = m_SoundStopQueue.front();
			m_SoundStopQueue.pop();
			lock.unlock();
			
			std::unique_lock<std::mutex> soundLock(m_SoundsMtx);

			auto loc = m_Sounds.find(soundId);
			if (loc == m_Sounds.end())
			{
				std::cout << std::format("Failed to find sound effect to stop with id: {}\n", soundId);
				continue;
			}

			auto& audioEffect = *(loc->second.pSoundEffect);
			audioEffect.StopEffect();
		}
		else if (m_SoundLoadQueue.size() != 0)	//load sound
		{
			auto soundEntry = m_SoundLoadQueue.front();
			m_SoundLoadQueue.pop();
			lock.unlock();

			std::unique_lock<std::mutex> soundLock(m_SoundsMtx);

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
			std::unique_lock<std::mutex> soundLock(m_SoundsMtx);

			auto loc = m_Sounds.find(soundId);
			if (loc == m_Sounds.end())
			{
				std::cout << std::format("Failed to find sound effect to unload with id: {}\n", soundId);
				continue;
			}

			loc->second.tokenAmount--;
			if (loc->second.tokenAmount <= 0)
			{
				loc->second.pSoundEffect->StopEffect();	//stop the sound effect before deleting it
				m_Sounds.erase(loc);
			}
		}
		else //play sound
		{
			auto [soundId, volume, loops] = m_SoundPlayQueue.front();
			m_SoundPlayQueue.pop();
			lock.unlock();
			std::unique_lock<std::mutex> soundLock(m_SoundsMtx);

			auto loc = m_Sounds.find(soundId);
			if (loc == m_Sounds.end())
			{
				std::cout << std::format("Failed to find sound effect to play with id: {}\n", soundId);
				continue;
			}

			auto& audioEffect = *(loc->second.pSoundEffect);
			audioEffect.SetVolume(volume);
			audioEffect.PlayEffect(loops);
		}
	}
}

//===================================================================================================================================================
//Logger_SoundSystem
//===================================================================================================================================================

dae::Logger_SoundSystem::Logger_SoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem)
	:s_pSoundSystem{ std::move(soundSystem) }
{
}

void dae::Logger_SoundSystem::Quit()
{
}

void dae::Logger_SoundSystem::SetGlobalVolume(sound_volume volume)
{
	std::cout << std::format("Setting global volume to: {}\n", volume);
	s_pSoundSystem->SetGlobalVolume(volume);
}

void dae::Logger_SoundSystem::PlayEffect(const SoundToken& soundToken, sound_volume volume, sound_loops loops)
{
	std::cout << std::format("Playing sound effect with id: {}\n", soundToken.GetId());
	s_pSoundSystem->PlayEffect(soundToken, volume, loops);
}

void dae::Logger_SoundSystem::StopEffect(const SoundToken& soundToken)
{
	std::cout << std::format("Stopping sound effect with id: {}\n", soundToken.GetId());
	s_pSoundSystem->StopEffect(soundToken);
}

void dae::Logger_SoundSystem::RegisterSound(const SoundEntry& soundEntry)
{
	std::cout << std::format("Registering sound effect\n\t\"{}\"\tid: {}\n", soundEntry.path, soundEntry.id);
	s_pSoundSystem->RegisterSound(soundEntry);
}

void dae::Logger_SoundSystem::UnregisterSound(sound_id id)
{
	std::cout << std::format("Unregistering sound effect with id: {}\n", id);
	s_pSoundSystem->UnregisterSound(id);
}