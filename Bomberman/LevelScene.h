#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <Scene.h>
#include <IObserver.h>
#include <vector>
#include <Sound.h>
#include <Command.h>
#include <InputManager.h>

namespace bm
{
	class TileComp;
	class LevelScene final : public dae::Scene, public dae::IObserver
	{
	public:

		LevelScene(int lives);

		// Inherited via Scene
		void Load() override;
		void Exit() override;
		std::unique_ptr<Scene> UpdateScene(float deltaTime) override;

	private:

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

		int m_PlayerLives;
		std::vector<dae::GameObjectHandle> m_PlayerHandles{};

		dae::GameObjectHandle m_TimerHandle;
		bool m_TimerFinished{ false };

		bool m_PlayerEscaped{ false };

		// Inherited via IObserver
		void Notify(dae::Event event, const std::any& data) override;

	};

	//levelstate stuff
	/*
	* std::vector<stageInfo> stages
	* int lives
	* int savedScore
	* bool soundEnabled
	*
	*/

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
}

#endif // !LEVELSCENE_H