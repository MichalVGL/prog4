#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::GameObject()
	:m_Components{}
	, m_IsCompFlaggedForDeletion{}
{
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
