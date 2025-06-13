#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <Scene.h>
#include <IObserver.h>
#include <vector>
#include <Sound.h>
#include <Command.h>
#include <InputManager.h>
#include "LevelUtils.h"

namespace bm
{
	class TileComp;
	class LevelScene final : public dae::Scene, public dae::IObserver
	{
	public:

		LevelScene(LevelInfo&& lvlInfo);

		// Inherited via Scene
		void Load() override;
		void Exit() override;
		std::unique_ptr<Scene> UpdateScene(float deltaTime) override;

		const LevelInfo& GetLevelInfo() const;

	private:
		friend class SkipLevelCommand;
		friend class RestartSoundtrackCommand;
		void RestartSoundtrack();

		//from base class
		void OnObjectAdded(dae::GameObjectHandle object) override;

		void SetupUI();
		void SpawnSafetyWalls(std::vector<bm::TileComp*> playerTiles); //lock the player in walls to not get spawnkilled

		//===============================================

		static constexpr float s_LevelTime{ 200.f };
		static constexpr dae::SoundEntry s_SoundtrackEntry{ "Sounds/Leveltrack.mp3" };

		dae::SoundToken m_SoundtrackToken{ s_SoundtrackEntry };
		std::unique_ptr<dae::KeyboardBinding> m_RestartSoundtrackBinding{};

		LevelInfo m_LevelInfo;
		StageInfo m_CurrentStageInfo{};

		std::vector<dae::GameObjectHandle> m_PlayerHandles{};

		dae::GameObjectHandle m_TimerHandle;
		bool m_TimerFinished{ false };

		bool m_PlayerEscaped{ false };

		//cheat
		std::unique_ptr<dae::KeyboardBinding> m_SkipLevelBinding{};

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

	};

	class RestartSoundtrackCommand final : public dae::Command
	{
	public:
		RestartSoundtrackCommand(LevelScene& levelScene)
			: m_Level{ levelScene }
		{
		}
		// Inherited via Command
		void Execute() override
		{
			m_Level.RestartSoundtrack();
		}

	private:
		LevelScene& m_Level;
	};

	class SkipLevelCommand final : public dae::Command
	{
	public:

		SkipLevelCommand(LevelScene& levelScene);

		// Inherited via Command
		void Execute() override;

	private:

		LevelScene& m_Level;

	};
}

#endif // !LEVELSCENE_H