//---------------------------
// Include Files
//---------------------------
#include "GameObject.h"
#include "Component.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Component::Component(dae::GameObject& parent)
	:m_GObjectParent{parent}
	, m_IsFlaggedForDeletion{ false }
{
}

Component::~Component()
{
	// nothing to destroy
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

const dae::GameObject& Component::GetOwner() const
{
	return m_GObjectParent;
}
