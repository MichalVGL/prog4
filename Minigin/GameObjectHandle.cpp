#include "GameObjectHandle.h"

#include <iostream>
#include <format>

#include "GameObject.h"

dae::GameObjectHandle::GameObjectHandle(GameObject* pGameObject)
	:m_pGameObject{ pGameObject }
{
	if (m_pGameObject != nullptr)
		m_pGameObject->RegisterHandle(this);
}

dae::GameObjectHandle::~GameObjectHandle()
{
	if (m_pGameObject)
		m_pGameObject->UnregisterHandle(this);
}

dae::GameObjectHandle::GameObjectHandle(const GameObjectHandle& other)
	:m_pGameObject{ other.m_pGameObject }
{
	if (m_pGameObject)
	{
		m_pGameObject->RegisterHandle(this);
	}
}

dae::GameObjectHandle::GameObjectHandle(GameObjectHandle&& other) noexcept
	:m_pGameObject{ other.m_pGameObject }
{
	if (m_pGameObject)
	{
		m_pGameObject->UnregisterHandle(&other);
		other.m_pGameObject = nullptr;
		m_pGameObject->RegisterHandle(this);
	}
}

dae::GameObjectHandle& dae::GameObjectHandle::operator=(const GameObjectHandle& other)
{
	if (this == &other)
		return *this; // Handle self-assignment

	if (m_pGameObject)
		m_pGameObject->UnregisterHandle(this);

	m_pGameObject = other.m_pGameObject;

	if (m_pGameObject)
		m_pGameObject->RegisterHandle(this);

	return *this;
}

dae::GameObjectHandle& dae::GameObjectHandle::operator=(GameObjectHandle&& other) noexcept
{
	if (this == &other)
		return *this; // Handle self-assignment

	if (m_pGameObject)
		m_pGameObject->UnregisterHandle(this);

	m_pGameObject = other.m_pGameObject;

	if (m_pGameObject)
	{
		m_pGameObject->UnregisterHandle(&other);
		other.m_pGameObject = nullptr; // Invalidate the moved-from handle
		m_pGameObject->RegisterHandle(this);
	}
	return *this;
}

dae::GameObject* dae::GameObjectHandle::Get() const
{
	return m_pGameObject;
}

dae::GameObject* dae::GameObjectHandle::operator->() const
{
	return m_pGameObject;
}

dae::GameObjectHandle::operator bool() const noexcept
{
	return m_pGameObject != nullptr;
}

void dae::GameObjectHandle::Invalidate()
{
	m_pGameObject = nullptr;
}
