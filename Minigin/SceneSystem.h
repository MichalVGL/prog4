#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "ISceneSystem.h"

#include <memory>

namespace dae
{
	class Null_SceneSystem final : public ISceneSystem
	{
	public:
		// Inherited via ISceneSystem
		Scene* GetCurrentScene() const override { return nullptr; };
		void LoadScene() override {};
		void Quit() override {};
		void Start() override {};
		void FixedUpdate(float) override {};
		void Update(float) override {};
		void LateUpdate(float) override {};
		void Render() const override {};
		void UpdateImGui() override {};
	};

	class Default_SceneSystem final : public ISceneSystem
	{
	public:

		Default_SceneSystem(std::unique_ptr<Scene>&& startScene);

		// Inherited via ISceneSystem
		Scene* GetCurrentScene() const override;
		void LoadScene() override;
		void Quit() override;

		void Start() override;
		void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		void LateUpdate(float deltaTime) override;
		void Render() const override;
		void UpdateImGui() override;

	private:

		std::unique_ptr<Scene> m_pScene{};
	};
}

#endif // !SCENESYSTEM_H
