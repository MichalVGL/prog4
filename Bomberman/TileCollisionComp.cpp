#include "TileCollisionComp.h"

#include <algorithm>

#include <ObjectFinder.h>

#include "BMServiceLocator.h"

bm::TileCollisionComp::TileCollisionComp(dae::GameObject& parent)
	:Component(parent)
{
}

void bm::TileCollisionComp::Update(float)
{
	if (m_TargetsDirty)
		SetTargets();

	CleanupTargets();	//check if any targets have been removed

	//check collisions
	auto& tileSystem = BMServiceLocator::GetTileSystem();
	auto* thisTileComp = tileSystem.GetTileFromWorldPos(GetOwner().GetWorldPos());
	if (thisTileComp == nullptr)
		return;	//no tile at this position, no collision possible
	for (const auto& target : m_Targets)
	{
		auto* otherTileComp = tileSystem.GetTileFromWorldPos(target->GetWorldPos());
		if (!otherTileComp)	//other object is not on a tile
			continue;
		if (otherTileComp->GetIndexPosition() == thisTileComp->GetIndexPosition())	//on the same tile
		{
			m_CollisionSubject.NotifyObservers(target);
		}
	}
}

void bm::TileCollisionComp::AddTarget(dae::GobjID targetId)
{
	if (std::find(m_TargetIds.begin(), m_TargetIds.end(), targetId) == m_TargetIds.end())
	{
		m_TargetIds.push_back(targetId);
		m_TargetsDirty = true;
	}
}

void bm::TileCollisionComp::RemoveTarget(dae::GobjID targetId)
{
	auto it = std::find(m_TargetIds.begin(), m_TargetIds.end(), targetId);
	if (it != m_TargetIds.end())
	{
		m_TargetIds.erase(it);
		m_TargetsDirty = true;
	}
}

void bm::TileCollisionComp::UpdateTargets()
{
	m_TargetsDirty = true;
}

dae::Subject& bm::TileCollisionComp::OnCollision()
{
	return m_CollisionSubject;
}

void bm::TileCollisionComp::SetTargets()
{
	m_Targets = dae::FindObjects(m_TargetIds);
	m_TargetsDirty = false;
}

void bm::TileCollisionComp::CleanupTargets()
{
	m_Targets.erase(std::remove_if(m_Targets.begin(), m_Targets.end(),
		[](dae::GameObjectHandle& handle)
		{return handle.Get() == nullptr; }), m_Targets.end());
}
