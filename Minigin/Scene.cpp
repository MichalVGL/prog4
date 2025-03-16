#include "Scene.h"

#include <algorithm>
#include <memory>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	: m_name{ name } 
{

}

Scene::~Scene() = default;

GameObject* Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
	return m_objects.back().get();
}

void Scene::Remove(GameObject* object)
{
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&object](const auto& gameObject) { return gameObject.get() == object; })
		, m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::Start()
{
	for (auto& object : m_objects)
	{
		object->Start();
	}
}

void dae::Scene::FixedUpdate(float deltaFixedTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(deltaFixedTime);
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->LateUpdate(deltaTime);
	}

	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(), [](const std::unique_ptr<GameObject>& obj)
			{
				return obj->IsFlaggedForDeletion();
			})
		, m_objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::UpdateImGui()
{
	for (const auto& object : m_objects)
	{
		object->UpdateImGui();
	}
}

