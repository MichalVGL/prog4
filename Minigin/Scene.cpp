#include "Scene.h"

#include <algorithm>

#include "ServiceLocator.h"

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
	for (auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.Update(deltaTime);
}

void dae::Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}

	RemoveFlaggedObjects();
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


//HELPERS=============

dae::Scene::Scene()
{
	m_Objects.reserve(s_MaxObjects); 
}

dae::GameObject* dae::Scene::Add(std::unique_ptr<GameObject> object)
{
	if (m_Objects.size() >= s_MaxObjects)
	{
		std::cout << std::format("Max amount of objects reached. Cannot add a new one.\n");
		return nullptr;
	}

	object->SetScene(this);
	if (m_HasStarted)
		object->Start();

	m_Objects.emplace_back(std::move(object));

	m_RenderSortedObjectsDirty = true;

	OnObjectAdded(m_Objects.back().get());
	return m_Objects.back().get();
}

void dae::Scene::RemoveAll()
{
	m_Objects.clear();
}

std::vector<dae::GameObjectHandle> dae::Scene::GetObjectsByID(GobjID id) const
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

void dae::Scene::UpdateHandles(std::vector<GameObjectHandle>& handles)
{
	handles.erase(
		std::remove_if(handles.begin(), handles.end(),
			[](const GameObjectHandle& handle)
			{
				return handle.Get() == nullptr;
			})
		, handles.end());
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
