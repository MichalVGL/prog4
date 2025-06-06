#include "BombComp.h"

#include "BMServiceLocator.h"

bm::BombComp::BombComp(dae::GameObject& parent)
	:Component(parent)
	, TileMod(parent, BOMB_MODID)
{
	m_TimerComp.Init(parent);
	m_TimerComp->SetTime(s_DetonationTime);
	m_TimerComp->OnTimerComplete().AddObserver(this);

	//setup sprite
	m_SpriteComp.Init(parent);
	m_SpriteComp->LoadTexture(s_BombTextureEntry);
	m_SpriteComp->SetFPS(GLOBAL_FPS);
	m_SpriteComp->AddSpriteEntry(s_BombSpriteEntry);
	m_SpriteComp->SetSpriteEntry(s_BombSpriteEntry.id);
	m_SpriteComp->SetAlignment(dae::HorizontalAlignment::center, dae::VerticalAlignment::center);
}

void bm::BombComp::OnDestroy()
{
	TileMod::Unregister();
	//todo spawn central fire
	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	spawnSystem.SpawnFire(GetOwner().GetWorldPos(), {}, Direction::all, 2);	//todo, add spread code
}

void bm::BombComp::Detonate()
{
	GetOwner().FlagForDeletion();	//will call ondestroy
}

void bm::BombComp::Notify(dae::Event event, const std::any&)
{
	if (event == TimerComp::s_TimerCompleteEvent)
	{
		Detonate();
		m_TimerComp->OnTimerComplete().RemoveObserver(this);
	}
}

bool bm::BombComp::IsWalkable() const
{
	return true;
}
