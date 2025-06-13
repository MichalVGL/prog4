#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

#include <vector>
#include <Texture.h>
#include <EngineComponents.h>

#include "BMServiceLocator.h"

namespace bm
{
	class MenuScene final : public dae::Scene
	{
	public:
		MenuScene(int achievedScore = 0);

		void Load() override;
		void Exit() override;
		std::unique_ptr<dae::Scene> UpdateScene(float deltaTime) override;

		void StartGame();

	private:

		static constexpr dae::TextureEntry s_MenuTitle{ "Textures/MenuTitle.png" };
		static constexpr dae::Color s_YellowColor{ .r = 189, .g = 189, .b = 0, .a = 255 };
		static constexpr dae::Color s_PurpleColor{ .r = 107, .g = 0, .b = 66, .a = 255 };

		bool m_StartCalled{ false };
		dae::GameObjectHandle m_ModeUIElementHandle{};

		int m_AchievedScore;	//score you got from the last level session
		const std::vector<HighScore>& m_HighScores;

	};
}
#endif // !MENUSCENE_H
