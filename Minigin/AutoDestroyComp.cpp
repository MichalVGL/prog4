#include "AutoDestroyComp.h"

dae::AutoDestroyComp::AutoDestroyComp(dae::GameObject& parent, float timeToDestroy)
	:Component(parent)
	, m_TimeRemaining{ timeToDestroy }
{
}

void dae::AutoDestroyComp::Update(float deltaTime)
{
	m_TimeRemaining -= deltaTime;
	if (m_TimeRemaining <= 0.f)
	{
		GetOwner().FlagForDeletion();
	}
}
