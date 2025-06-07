#include "Scene.h"

#include <algorithm>
#include <memory>

#include "ServiceLocator.h"

unsigned int dae::Scene::m_idCounter = 0;

dae::Scene::Scene(const std::string& name)
	: m_name{ name } 
{
}

void dae::Scene::RemoveFlaggedObjects()
{
	m_Objects.erase(
		std::remove_if(m_Objects.begin(), m_Objects.end(), [&](const std::unique_ptr<GameObject>& obj)
			{
				if (obj->IsFlaggedForDeletion())
				{
					m_RenderSortedObjectsDirty = true; //if an object is flagged for deletion, we need to sort the render objects again
					return true;
				}
				else
					return false;
			})
		, m_Objects.end());
}

void dae::Scene::SortRenderObjects() const
{
	m_RenderSortedObjects.clear();
	m_RenderSortedObjects.reserve(m_Objects.size());	

	//copy the pointers
	std::transform(m_Objects.begin(), m_Objects.end(), std::back_inserter(m_RenderSortedObjects),
		[](const std::unique_ptr<GameObject>& obj) { return obj.get(); });

	std::sort(m_RenderSortedObjects.begin(), m_RenderSortedObjects.end(),
		[](const GameObject* a, const GameObject* b)
		{
			return a->GetRenderLayer() < b->GetRenderLayer();
		});

	m_RenderSortedObjectsDirty = false; 
}

dae::Scene::~Scene() = default;

dae::GameObject* dae::Scene::Add(std::unique_ptr<GameObject> object)
{
	object->SetScene(this);
	if (m_HasStarted)
		object->Start();

	m_Objects.emplace_back(std::move(object));

	m_RenderSortedObjectsDirty = true;
	return m_Objects.back().get();
}

void dae::Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::Start()
{
	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.Start();

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

void dae::Scene::Update(float deltaTime)
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

	RemoveFlaggedObjects();

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.Update(deltaTime);
}

void dae::Scene::Render() const
{
	if (m_RenderSortedObjectsDirty)
	{
		SortRenderObjects();
	}
	for (const auto* object : m_RenderSortedObjects)
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

std::vector<dae::GameObjectHandle> dae::Scene::GetObjectByID(GobjID id) const
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