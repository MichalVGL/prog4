#include "SimpleCollisionComp.h"

#include <algorithm>

#include "ObjectFinder.h"
#include "utils.h"

dae::SimpleCollisionComp::SimpleCollisionComp(dae::GameObject& parent)
	:Component(parent)
{
}

void dae::SimpleCollisionComp::Update(float)
{
	if (m_TargetsDirty)
		SetTargets();

	CleanupTargets();	//check if any targets have been removed

	for (const auto& target : m_Targets)
	{
		float distSq = dae::LengthSquared(target->GetWorldPos() - GetOwner().GetWorldPos());
		if (distSq - (m_Radius * m_Radius) < 0.f)
		{
			m_CollisionSubject.NotifyObservers(target);
		}
	}
}

void dae::SimpleCollisionComp::SetRadius(float radius)
{
	if(radius > 0.01f)
		m_Radius = radius;
}

void dae::SimpleCollisionComp::AddTarget(dae::GobjID targetId)
{
	if (std::find(m_TargetIds.begin(), m_TargetIds.end(), targetId) == m_TargetIds.end())
	{
		m_TargetIds.push_back(targetId);
		m_TargetsDirty = true;
	}
}

void dae::SimpleCollisionComp::RemoveTarget(dae::GobjID targetId)
{
	auto it = std::find(m_TargetIds.begin(), m_TargetIds.end(), targetId);
	if (it != m_TargetIds.end())
	{
		m_TargetIds.erase(it);
		m_TargetsDirty = true;
	}
}

void dae::SimpleCollisionComp::UpdateTargets()
{
	m_TargetsDirty = true;
}

dae::Subject& dae::SimpleCollisionComp::OnCollision()
{
	return m_CollisionSubject;
}

void dae::SimpleCollisionComp::SetTargets()
{
	m_Targets = dae::FindObjects(m_TargetIds);
	m_TargetsDirty = false;
}

void dae::SimpleCollisionComp::CleanupTargets()
{
	m_Targets.erase(std::remove_if(m_Targets.begin(), m_Targets.end(), [](dae::GameObjectHandle& handle)
		{ return handle.Get() == nullptr; }), m_Targets.end());
}