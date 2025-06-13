#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H

#include <Scene.h>
#include <vector>
#include <Texture.h>
#include <InputManager.h>

namespace bm
{
	class HighScoreScene final : public dae::Scene
	{
	public:
		HighScoreScene();
		// Inherited via Scene
		void Load() override;
		void Exit() override;
		std::unique_ptr<Scene> UpdateScene(float deltaTime) override;

		void ConfirmSelection();

	private:

		static constexpr int s_AmountOfChars{6};
		static constexpr dae::Color s_YellowColor{ .r = 189, .g = 189, .b = 0, .a = 255 };

		std::vector<dae::GameObjectHandle> m_HighScoreTextHandles{};

		bool m_Confirmed{ false };

	};
}
#endif // !HIGHSCORESCENE_H
