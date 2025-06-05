#include "WallComp.h"

#include "BMGameDefines.h"

bm::WallComp::WallComp(dae::GameObject& parent)
	:Component(parent), TileMod(WALL_MODID, parent)
{
	//setup sprite
	m_SpriteComp.Init(parent);
	m_SpriteComp->LoadTexture(s_WallTextureEntry);
	m_SpriteComp->SetFPS(GLOBAL_FPS);
	m_SpriteComp->AddSpriteEntry(s_BaseWallSprite);
	m_SpriteComp->AddSpriteEntry(s_DestroyingWallSprite);

	m_SpriteComp->SetSpriteEntry(s_BaseWallSprite.id);
}

void bm::WallComp::Update(float deltaTime)
{
	deltaTime;
	if (m_IsBeingDestroyed && m_SpriteComp->IsLoopComplete())
	{
		//todo delete this and spawn a tilemod if there is one stored
	}
}

void bm::WallComp::Destroy()
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
