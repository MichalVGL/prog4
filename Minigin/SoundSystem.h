#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <unordered_map>

#include "ISoundSystem.h"
#include "SoundEffect.h"
#include "SoundToken.h"

namespace dae
{
	struct SoundResource
	{
		std::unique_ptr<SoundEffect> pSoundEffect;
		int tokenAmount{ 0 };

		SoundResource(const std::string& path)
			: pSoundEffect{ std::make_unique<SoundEffect>(path) }
		{
		}
	};

		
	//Null_SoundSystem=====================================================================================================
	class Null_SoundSystem final : public ISoundSystem
	{
	public:
		void SetGlobalVolume(sound_volume) override {};
	private:
		void PlayEffect(const SoundToken&, sound_volume) override {};
		void RegisterSound(const SoundEntry&) override {};
		void UnregisterSound(sound_effect_id) override {};
	};

	//SDL_SoundSystem======================================================================================================
	class SDL_SoundSystem final : public ISoundSystem
	{
	public:
		SDL_SoundSystem(std::filesystem::path dataPath);

		~SDL_SoundSystem();
		SDL_SoundSystem(const SDL_SoundSystem&) = delete;
		SDL_SoundSystem(SDL_SoundSystem&&) = delete;
		SDL_SoundSystem& operator=(const SDL_SoundSystem&) = delete;
		SDL_SoundSystem& operator=(SDL_SoundSystem&&) = delete;

		void SetGlobalVolume(sound_volume volume) override;

	private:

		void PlayEffect(const SoundToken& soundToken, sound_volume volume) override;

		void RegisterSound(const SoundEntry& soundEntry) override;
		void UnregisterSound(sound_effect_id id) override;
		
		//base resources
		std::filesystem::path m_DataPath;
		sound_volume m_GlobalVolume{ 1.f };
		std::unordered_map<sound_effect_id, SoundResource> m_Sounds{};

		//shared resources with thread
		std::queue<std::pair<sound_effect_id, sound_volume>> m_SoundPlayQueue{};
		std::queue<SoundEntry> m_SoundLoadQueue{};
		std::queue<sound_effect_id> m_SoundUnloadQueue{};

		//thread related vars
		std::mutex m_Mtx{};
		std::condition_variable m_CV{};
		std::jthread m_SDLThread;

		void SoundThread(std::stop_token stopToken);
	};

	//Logger_SoundSystem=====================================================================================================
	class Logger_SoundSystem final : public ISoundSystem
	{
	public:

		Logger_SoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem);

		void SetGlobalVolume(sound_volume volume) override;

	private:

		void PlayEffect(const SoundToken& soundToken, sound_volume volume) override;

		void RegisterSound(const SoundEntry& soundEntry) override;
		void UnregisterSound(sound_effect_id id) override;
	
		std::unique_ptr<ISoundSystem> m_pSoundSystem;
	};
}

#endif // !SOUNDSYSTEM_H
