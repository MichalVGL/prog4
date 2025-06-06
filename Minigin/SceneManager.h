#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);	//todo, change to loadscene with some kind of scenedetail system

		Scene* GetCurrentScene() const;

		void Start();
		void FixedUpdate(float deltaFixedTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		void UpdateImGui();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		//std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<Scene> m_pScene{};
	};
}

#endif // SCENEMANAGER_H