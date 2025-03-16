#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComp.h"

dae::GameObject::GameObject()
	:m_Components{}
	, m_IsCompFlaggedForDeletion{}
	, m_ChildrenGameObj{}
	, m_pParentGameObj{}
	, m_WorldPos{}
	, m_IsWorldPosValid{}
{
	//do not use AddComponent() due to that function not accepting transformComp
	m_Components.emplace_back(std::make_unique<TransformComp>(*this));
	m_pTransformComp = static_cast<TransformComp*>(m_Components.at(0).get());
}

dae::GameObject::~GameObject()
{
	for (auto& child : m_ChildrenGameObj)
	{
		child->SetParent(m_pParentGameObj);
	}

	if(m_pParentGameObj != nullptr)
		m_pParentGameObj->RemoveChild(this);
}

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

void dae::GameObject::UpdateImGui()
{
	for (auto& comp : m_Components)
	{
		comp->UpdateImGui();
	}
}

void dae::GameObject::FlagForDeletion()
{
	m_FlaggedForDeletion = true;
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
			m_pTransformComp->SetLocalPosition(GetWorldPos() - parent->GetWorldPos());
		else
			m_pTransformComp->SetLocalPosition(GetWorldPos());
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
	return m_pTransformComp->GetLocalPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec2& pos)
{
	m_pTransformComp->SetLocalPosition(pos);
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
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
	m_WorldPos = m_pTransformComp->GetLocalPosition();
	if (m_pParentGameObj != nullptr)
	{
		m_WorldPos += m_pParentGameObj->GetWorldPos();
	}

	m_IsWorldPosValid = true;
	return m_WorldPos;
}
