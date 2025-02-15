#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

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
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components)
	{
		comp->Render();
	}
}
