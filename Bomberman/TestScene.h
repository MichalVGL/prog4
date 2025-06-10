#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <Scene.h>

namespace bm
{
	class TestScene final : public dae::Scene
	{
	public:

		TestScene() = default;

		// Inherited via Scene
		void Load() override;
		void Exit() override;
		std::unique_ptr<Scene> UpdateScene(float deltaTime) override;

	private:

		dae::GameObjectHandle m_Player{};

	};
}

#endif // !TESTSCENE_H
