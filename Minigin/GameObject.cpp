#include "GameObject.h"

#include <algorithm>

#include "GameObjectHandle.h"
#include "TransformComp.h"
#include "Scene.h"

dae::GameObject::GameObject(const GobjID& name, render_layer rLayer)
	:m_Id{name}
	, m_Components{}
	, m_RenderLayer{ rLayer }
{
	//do not use AddComponent() due to that function not accepting transformComp
	m_Components.emplace_back(std::make_unique<TransformComp>(*this));
	m_TransformComp = static_cast<TransformComp*>(m_Components.at(0).get());
}

dae::GameObject::~GameObject()
{
	//parent/children system
	std::for_each(m_ChildrenGameObj.rbegin(), m_ChildrenGameObj.rend(), [this](GameObject* child)
		{
			child->SetParent(m_pParentGameObj);
		});

	if(m_pParentGameObj != nullptr)
		m_pParentGameObj->RemoveChild(this);

	//handles
	for (auto& handle : m_RegisteredHandles)
	{
		handle->Invalidate();
	}
}

void dae::GameObject::Start()
{
	if (m_pScene == nullptr)
		std::cout << std::format("Warning: GameObject ({}) doesn't have it's scene setup\n", GetName());

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
		assert(comp != nullptr && "Component is nullptr, this should never happen");
		comp->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (auto& comp : m_Components)
	{
		comp->LateUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components)
	{
		comp->Render();
	}
}

void dae::GameObject::UpdateImGui()
{
	for (auto& comp : m_Components)
	{
		comp->UpdateImGui();
	}
}

std::string_view dae::GameObject::GetName() const
{
	if (m_Id.name != s_NullName)
		return m_Id.name;
	else
		return "unnamed";
}

const dae::GobjID& dae::GameObject::GetId() const
{
	return m_Id;
}

void dae::GameObject::FlagForDeletion()
{
	if (!m_FlaggedForDeletion)	//prevent calling multiple times
	{
		m_FlaggedForDeletion = true;
		for (auto& comp : m_Components)
		{
			comp->OnDestroy();
		}
	}
}

bool dae::GameObject::IsFlaggedForDeletion() const
{
	return m_FlaggedForDeletion;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	//check if parent is valid
	assert(parent != this && "Tried to set the parent GameObject to itself");
	assert(!HasChild(parent) && "Cannot set the parent to one of its child GameObjects");

	//update position
	InvalidateWorldPos();
	if (keepWorldPos)
	{
		if (parent != nullptr)
			m_TransformComp->SetLocalPosition(GetWorldPos() - parent->GetWorldPos());
		else
			m_TransformComp->SetLocalPosition(GetWorldPos());
	}

	//assign/unassign other gameObjects
	if (m_pParentGameObj != nullptr)
		m_pParentGameObj->RemoveChild(this);

	m_pParentGameObj = parent;

	if(m_pParentGameObj != nullptr)
		m_pParentGameObj->AddChild(this);
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParentGameObj;
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
{
	return m_ChildrenGameObj;
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_ChildrenGameObj.size());
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	assert(index < static_cast<int>(m_ChildrenGameObj.size()) && (index >= 0)
		&& "Attempted to get a child GameObject at an invalid index");
	return m_ChildrenGameObj.at(index);
}

bool dae::GameObject::HasChild(GameObject* child) const
{
	for (auto* childObject : m_ChildrenGameObj)
	{
		if (childObject == child || childObject->HasChild(child))
			return true;
	}
	return false;
}

const glm::vec2& dae::GameObject::GetWorldPos()
{
	if (m_IsWorldPosValid)
	{
		return m_WorldPos;
	}
	else
	{
		return CalculateWorldPos();
	}
}

void dae::GameObject::InvalidateWorldPos()
{
	m_IsWorldPosValid = false;
	for (auto& child : m_ChildrenGameObj)
	{
		child->InvalidateWorldPos();
	}
}

const glm::vec2& dae::GameObject::GetLocalPosition()
{
	return m_TransformComp->GetLocalPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec2& pos)
{
	m_TransformComp->SetLocalPosition(pos);
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
}

dae::Scene& dae::GameObject::GetScene()
{
	return *m_pScene;	//this pointer is salways set. If not, a warning will be printed on start(). (When the scene gets an gameobject, it will set this variable)
}

dae::render_layer dae::GameObject::GetRenderLayer() const
{
	return m_RenderLayer;
}

void dae::GameObject::RegisterHandle(GameObjectHandle* handle)
{
	if (handle == nullptr)
	{
		std::cout << "Warning: GameObjectHandle is nullptr, cannot register\n";
		return;
	}
	m_RegisteredHandles.emplace_back(handle);
}

void dae::GameObject::UnregisterHandle(GameObjectHandle* handle)
{
	if (handle == nullptr)
	{
		std::cout << "Warning: GameObjectHandle is nullptr, cannot unregister\n";
		return;
	}
	auto it = std::find(m_RegisteredHandles.begin(), m_RegisteredHandles.end(), handle);
	if (it != m_RegisteredHandles.end())
	{
		m_RegisteredHandles.erase(it);
	}
	else
	{
		std::cout << "Warning: GameObjectHandle not found, cannot unregister\n";
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_ChildrenGameObj.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	assert(HasChild(child) && "Tried to remove a child that the GameObject doesn't have");

	std::erase(m_ChildrenGameObj, child);
}

const glm::vec2& dae::GameObject::CalculateWorldPos()
{
	m_WorldPos = m_TransformComp->GetLocalPosition();
	if (m_pParentGameObj != nullptr)
	{
		m_WorldPos += m_pParentGameObj->GetWorldPos();
	}

	m_IsWorldPosValid = true;
	return m_WorldPos;
}

void dae::GameObject::SetScene(Scene* scene)
{
	m_pScene = scene;
}
