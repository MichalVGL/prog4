#include "SceneSystem.h"

#include "ServiceLocator.h"

dae::Default_SceneSystem::Default_SceneSystem(std::unique_ptr<Scene>&& startScene)
	:m_pScene{ std::move(startScene) }
{
}

dae::Scene* dae::Default_SceneSystem::GetCurrentScene() const
{
	return m_pScene.get();
}

void dae::Default_SceneSystem::LoadScene()
{
	m_pScene->Load();
}

void dae::Default_SceneSystem::Start()
{
	if (m_pScene)
		m_pScene->Start();
}

void dae::Default_SceneSystem::FixedUpdate(float deltaFixedTime)
{
	if (m_pScene)
		m_pScene->FixedUpdate(deltaFixedTime);
}

void dae::Default_SceneSystem::Update(float deltaTime)
{
	if (m_pScene)
		m_pScene->Update(deltaTime);
}

void dae::Default_SceneSystem::LateUpdate(float deltaTime)
{
	if (m_pScene)
		m_pScene->LateUpdate(deltaTime);

	auto newScene = m_pScene->UpdateScene(deltaTime);
	if (newScene)
	{
		m_pScene->Exit();
		m_pScene->RemoveAll();
		ServiceLocator::GetTextureSystem().UnloadUnusedResources();
		m_pScene = std::move(newScene);
		m_pScene->Load(); //load the scene itself
		Start(); // Call Start on the new scene to initialize it	
	}
}

void dae::Default_SceneSystem::Render() const
{
	if (m_pScene)
		m_pScene->Render();
}

void dae::Default_SceneSystem::UpdateImGui()
{
	if (m_pScene)
		m_pScene->UpdateImGui();
}
