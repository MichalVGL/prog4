#include "WallComp.h"

#include "BMGameDefines.h"

bm::WallComp::WallComp(dae::GameObject& parent)
	:Component(parent), TileMod(parent, WALL_MODID)
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

void bm::WallComp::Update(float deltaTime)
{
	deltaTime;
	if (m_IsBeingDestroyed && m_SpriteComp->IsLoopComplete())
	{
		GetOwner().FlagForDeletion();
	}
}

void bm::WallComp::OnDestroy()
{
	TileMod::Unregister();
	//todo spawn stored mod
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
