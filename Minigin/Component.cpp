//---------------------------
// Include Files
//---------------------------
#include "Component.h"

dae::Component::Component(dae::GameObject& parent)
	:m_GObjectParent{parent}
	, m_IsFlaggedForDeletion{ false }
{
}

void dae::Component::Start()
{
}

void dae::Component::FixedUpdate(float)
{
}

void dae::Component::Update(float)
{
}

void dae::Component::LateUpdate(float)
{
}

void dae::Component::UpdateImGui()
{
}

void dae::Component::OnDestroy()
{
}

void dae::Component::Render() const
{
}

void dae::Component::FlagForDeletion()
{
	m_IsFlaggedForDeletion = true;
}

bool dae::Component::IsFlaggedForDeletion() const
{
	return m_IsFlaggedForDeletion;
}

dae::GameObject& dae::Component::GetOwner() const
{
	return m_GObjectParent;
}