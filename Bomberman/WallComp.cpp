#include "WallComp.h"

#include "BMGameDefines.h"
#include "BMServiceLocator.h"

bm::WallComp::WallComp(dae::GameObject& parent, ContainedObject object)
	:Component(parent), TileMod(parent, WALL_MODID)
	, m_ContainedObject{ object }
{
	//setup sprite
	m_SpriteComp.Init(parent);
	m_SpriteComp->LoadTexture(s_WallTextureEntry);
	m_SpriteComp->SetFPS(GLOBAL_FPS);
	m_SpriteComp->SetAlignment(dae::HorizontalAlignment::center, dae::VerticalAlignment::center);
	m_SpriteComp->AddSpriteEntry(s_BaseWallSprite);
	m_SpriteComp->AddSpriteEntry(s_DestroyingWallSprite);

	m_SpriteComp->SetSpriteEntry(s_BaseWallSprite.id);
}

void bm::WallComp::Update(float)
{
	if (m_IsBeingDestroyed && m_SpriteComp->IsLoopComplete())
	{
		GetOwner().FlagForDeletion();
	}
}

void bm::WallComp::OnDestroy()
{
	TileMod::Unregister();

	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	switch (m_ContainedObject)
	{
	case bm::ContainedObject::upgrade:
		spawnSystem.SpawnRandomUpgrade(GetOwner().GetWorldPos());
		break;
	case bm::ContainedObject::door:
		spawnSystem.SpawnDoor(GetOwner().GetWorldPos());
		break;
	}
}

void bm::WallComp::DestroyWall()
{
	if (m_IsBeingDestroyed == false)
	{
		m_IsBeingDestroyed = true;
		m_SpriteComp->SetSpriteEntry(s_DestroyingWallSprite.id);
	}
}

bool bm::WallComp::IsWalkable() const
{
	return false;
}
