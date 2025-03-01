#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Start()
{
	for (auto& scene : m_scenes)
	{
		scene->Start();
	}
}

void dae::SceneManager::FixedUpdate(float deltaFixedTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaFixedTime);
	}
}

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::LateUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate(deltaTime);
	}
}

void dae::SceneManager::Render() const 
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::UpdateImGui()
{
	for (const auto& scene : m_scenes)
	{
		scene->UpdateImGui();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
