//---------------------------
// Include Files
//---------------------------
#include "Component.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Component::Component(dae::GameObject& parent)
	:m_GObjectParent{parent}
	, m_IsFlaggedForDeletion{ false }
{
}

void Component::Start()
{
}

void Component::FixedUpdate(float)
{
}

void Component::Update(float)
{
}

void Component::LateUpdate(float)
{
}

void Component::FlagForDeletion()
{
	m_IsFlaggedForDeletion = true;
}

bool Component::IsFlaggedForDeletion() const
{
	return m_IsFlaggedForDeletion;
}

dae::GameObject& Component::GetOwner() const
{
	return m_GObjectParent;
}