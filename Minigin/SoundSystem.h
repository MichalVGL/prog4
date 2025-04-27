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

namespace dae
{
	//Null_SoundSystem=====================================================================================================
	class Null_SoundSystem final : public ISoundSystem
	{
	public:
		void PlayEffect(const SoundEntry&, float) override {};
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

		void PlayEffect(const SoundEntry& soundEntry, sound_volume volume) override;

	private:

		std::filesystem::path m_DataPath;
		std::queue<std::pair<SoundEntry, sound_volume>> m_SoundQueue{};
		std::unordered_map<sound_effect_id, SoundEffect> m_SoundEffects{};

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

		void PlayEffect(const SoundEntry& soundEntry, sound_volume volume) override;

	private:

		std::unique_ptr<ISoundSystem> m_pSoundSystem;

	};
}

#endif // !SOUNDSYSTEM_H
