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

		Null_SoundSystem() = default;
		~Null_SoundSystem() = default;
		Null_SoundSystem(const Null_SoundSystem&) = delete;
		Null_SoundSystem(Null_SoundSystem&&) = delete;
		Null_SoundSystem& operator=(const Null_SoundSystem&) = delete;
		Null_SoundSystem& operator=(Null_SoundSystem&&) = delete;

		void Quit() override {};

		void SetGlobalVolume(sound_volume) override {};
	private:
		void PlayEffect(const SoundToken&, sound_volume, sound_loops) override {};
		void StopEffect(const SoundToken&) override {};
		bool IsPlayingEffect(const SoundToken&) const override { return false; };
		void RegisterSound(const SoundEntry&) override {};
		void UnregisterSound(sound_id) override {};
	};

	//SDL_SoundSystem======================================================================================================
	class SDL_SoundSystem final : public ISoundSystem
	{
	public:
		SDL_SoundSystem(std::filesystem::path dataPath);

		~SDL_SoundSystem() = default;
		SDL_SoundSystem(const SDL_SoundSystem&) = delete;
		SDL_SoundSystem(SDL_SoundSystem&&) = delete;
		SDL_SoundSystem& operator=(const SDL_SoundSystem&) = delete;
		SDL_SoundSystem& operator=(SDL_SoundSystem&&) = delete;

		void Quit() override;

		void SetGlobalVolume(sound_volume volume) override;

	private:

		void PlayEffect(const SoundToken& soundToken, sound_volume volume, sound_loops loops) override;
		void StopEffect(const SoundToken& soundToken) override;
		bool IsPlayingEffect(const SoundToken& soundToken) const override;

		void RegisterSound(const SoundEntry& soundEntry) override;
		void UnregisterSound(sound_id id) override;
		
		//base resources
		std::filesystem::path m_DataPath;
		sound_volume m_GlobalVolume{ 1.f };
		std::unordered_map<sound_id, SoundResource> m_Sounds{};

		//shared resources with thread
		std::queue<std::tuple<sound_id, sound_volume, sound_loops>> m_SoundPlayQueue{};
		std::queue<sound_id> m_SoundStopQueue{};
		std::queue<SoundEntry> m_SoundLoadQueue{};
		std::queue<sound_id> m_SoundUnloadQueue{};

		//thread related vars
		mutable std::mutex m_QueueMtx{};
		mutable std::mutex m_SoundsMtx{};
		std::condition_variable m_CV{};
		std::jthread m_SDLThread;

		void SoundThread(std::stop_token stopToken);
	};

	//Logger_SoundSystem=====================================================================================================
	class Logger_SoundSystem final : public ISoundSystem
	{
	public:

		Logger_SoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem);

		~Logger_SoundSystem() = default;
		Logger_SoundSystem(const Logger_SoundSystem&) = delete;
		Logger_SoundSystem(Logger_SoundSystem&&) = delete;
		Logger_SoundSystem& operator=(const Logger_SoundSystem&) = delete;
		Logger_SoundSystem& operator=(Logger_SoundSystem&&) = delete;

		void Quit() override;

		void SetGlobalVolume(sound_volume volume) override;

	private:

		void PlayEffect(const SoundToken& soundToken, sound_volume volume, sound_loops loops) override;
		void StopEffect(const SoundToken& soundToken) override;
		void RegisterSound(const SoundEntry& soundEntry) override;
		void UnregisterSound(sound_id id) override;
	
		std::unique_ptr<ISoundSystem> s_pSoundSystem;
	};
}

#endif // !SOUNDSYSTEM_H
