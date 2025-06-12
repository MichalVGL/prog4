#include "BombermanComp.h"

bm::BombermanComp::BombermanComp(dae::GameObject& parent)
	:Component(parent)
{
}

void bm::BombermanComp::Start()
{
	m_EntityComp.Init(GetOwner());

	m_EntityComp->SetWalkSound(&m_WalkSoundToken);
}
