#ifndef STARTSTAGESCENE_H
#define STARTSTAGESCENE_H

#include <Scene.h>
#include <Sound.h>

namespace bm
{
	class LevelScene;
	class StartStageScene final : public dae::Scene
	{
	public:

		StartStageScene(std::unique_ptr<dae::Scene>&& scene);

		// Inherited via Scene
		void Load() override;
		void Exit() override;
		std::unique_ptr<Scene> UpdateScene(float deltaTime) override;

	private:

		static constexpr dae::SoundEntry s_SoundtrackEntry{ "Sounds/StageStart.mp3" };

		dae::SoundToken m_SoundtrackToken{ s_SoundtrackEntry };

		float m_RemainingTime{ 3.4f };

		std::unique_ptr<dae::Scene> m_LevelScene;

	};
}

#endif // !STARTSTAGESCENE_H
