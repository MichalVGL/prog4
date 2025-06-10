#include "EnemyComp.h"

#include "BMGameDefines.h"
#include "EntityComp.h"

bm::EnemyComp::EnemyComp(dae::GameObject& parent)
	:Component(parent)
{
	m_SimpleCollisionComp.Init(parent);

	m_SimpleCollisionComp->SetRadius(s_HitRadius);
	m_SimpleCollisionComp->AddTarget(PLAYER_GOBJID);
	m_SimpleCollisionComp->OnCollision().AddObserver(this);
}

void bm::EnemyComp::Notify(dae::Event event, const std::any& data)
{
	if (event == dae::SimpleCollisionComp::s_CollisionEvent)
	{
		auto player = std::any_cast<dae::GameObjectHandle>(data);
		if (player.Get() == nullptr || player->GetId() != PLAYER_GOBJID)
			return;

		player->GetComponent<bm::EntityComp>()->Kill();
	}
}
