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
	object->SetScene(this);
	if (m_HasStarted)
		object->Start();

	m_Objects.emplace_back(std::move(object));
	return m_Objects.back().get();
}

void Scene::Remove(GameObject* object)
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&object](const auto& gameObject) { return gameObject.get() == object; })
		, m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::Start()
{
	for (auto& object : m_Objects)
	{
		object->Start();
	}
	m_HasStarted = true;
}

void dae::Scene::FixedUpdate(float deltaFixedTime)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaFixedTime);
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}

	m_Objects.erase(
		std::remove_if(m_Objects.begin(), m_Objects.end(), [](const std::unique_ptr<GameObject>& obj)
			{
				return obj->IsFlaggedForDeletion();
			})
		, m_Objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::UpdateImGui()
{
	for (const auto& object : m_Objects)
	{
		object->UpdateImGui();
	}
}

std::vector<GameObjectHandle> dae::Scene::GetObjectByID(GobjID id) const
{
	std::vector<GameObjectHandle> handles{};
	for (const auto& object : m_Objects)
	{
		if (object->GetId() == id)
		{
			handles.emplace_back(dae::GameObjectHandle(object.get()));
		}
	}
	return handles;
}