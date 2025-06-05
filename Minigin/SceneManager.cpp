#include "SceneManager.h"
#include "Scene.h"

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	//m_scenes.push_back(scene);
	//m_pScene = std::make_shared<Scene>(name);
	m_pScene = std::shared_ptr<Scene>(new Scene(name));
	return *m_pScene;
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	return m_pScene.get();
}

void dae::SceneManager::Start()
{
	if (m_pScene)
		m_pScene->Start();
}

void dae::SceneManager::FixedUpdate(float deltaFixedTime)
{
	if (m_pScene)
		m_pScene->FixedUpdate(deltaFixedTime);
}

void dae::SceneManager::Update(float deltaTime)
{
	if (m_pScene)
		m_pScene->Update(deltaTime);
}

void dae::SceneManager::LateUpdate(float deltaTime)
{
	if (m_pScene)
		m_pScene->LateUpdate(deltaTime);
}

void dae::SceneManager::Render() const
{
	if (m_pScene)
		m_pScene->Render();
}

void dae::SceneManager::UpdateImGui()
{
	if (m_pScene)
		m_pScene->UpdateImGui();
}
