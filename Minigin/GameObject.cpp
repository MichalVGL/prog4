#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComp.h"

dae::GameObject::GameObject()
	:m_Components{}
	, m_IsCompFlaggedForDeletion{}
	, m_ChildGameObjects{}
	, m_pParentGameObject{}
{
	//AddComponent(std::make_unique<TransformComp>(*this));
	m_Components.push_back(std::make_unique<TransformComp>(*this));
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (auto& comp : m_Components)
	{
		comp->Start();
	}
}

void dae::GameObject::FixedUpdate(float deltaFixedTime)
{
	for (auto& comp : m_Components)
	{
		comp->FixedUpdate(deltaFixedTime);
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (auto& comp : m_Components)
	{
		comp->LateUpdate(deltaTime);
	}

	//erase components that are flagged
	if (m_IsCompFlaggedForDeletion)
	{
		m_Components.erase(
			std::remove_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& comp)
			{
				return comp->IsFlaggedForDeletion();
			})
			, m_Components.end());
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components)
	{
		comp->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	//check if parent is valid
	assert(parent != this && "Tried to set the parent GameObject to itself");
	assert(!HasChild(parent) && "Cannot set the parent to one of its child GameObjects");

	if (m_pParentGameObject != nullptr)
		m_pParentGameObject->RemoveChild(this);

	m_pParentGameObject = parent;

	if(parent != nullptr)
		m_pParentGameObject->AddChild(this);

	//todo set flag to update position
	keepWorldPos;	//todo add position calculation
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParentGameObject;
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_ChildGameObjects.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	assert(m_ChildGameObjects.size() < index && "");
	return nullptr;
}

bool dae::GameObject::HasChild(GameObject* child) const
{
	for (auto* childObject : m_ChildGameObjects)
	{
		if (childObject == child || childObject->HasChild(child))
			return true;
	}
	return false;
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_ChildGameObjects.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto loc = std::find(m_ChildGameObjects.begin(), m_ChildGameObjects.end(), child);
	assert(loc != m_ChildGameObjects.end() && "Tried to remove a child that the GameObject doesn't have");

	m_ChildGameObjects.erase(loc);
}
