#include "UpgradeComp.h"

#include "BMGameDefines.h"
#include "EntityComp.h"
#include "BMServiceLocator.h"

bm::UpgradeComp::UpgradeComp(dae::GameObject& parent, UpgradeType type)
	:Component(parent)
	, TileMod{parent, UPGRADE_MODID}
	, m_Type{ type }
{
	m_TileCollisionComp.Init(GetOwner());
	m_RenderComp.Init(GetOwner());

	//setup collision
	m_TileCollisionComp->AddTarget(bm::PLAYER_GOBJID);
	m_TileCollisionComp->OnCollision().AddObserver(this);

	//setup texture
	switch (type)
	{
	case bm::UpgradeType::remoteDetonator:
		m_RenderComp->LoadImageTexture(s_RemoteControlTextureEntry);
		break;
	case bm::UpgradeType::bombCount:
		m_RenderComp->LoadImageTexture(s_PowerUpTextureEntry);
		break;
	case bm::UpgradeType::bombRange:
		m_RenderComp->LoadImageTexture(s_FireUpTextureEntry);
		break;
	}
	m_RenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	m_RenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	m_RenderKey = m_RenderComp->Lock();
}

void bm::UpgradeComp::OnDestroy()
{
	TileMod::Unregister();
}

bool bm::UpgradeComp::IsWalkable() const
{
	return true;
}

void bm::UpgradeComp::Notify(dae::Event event, const std::any& data)
{
	if (event.id == TileCollisionComp::s_CollisionEvent.id)
	{
		auto target = std::any_cast<dae::GameObjectHandle>(data);
		if (target.Get() == nullptr)
			return;	//no target to handle
		if (target->GetId() == bm::PLAYER_GOBJID)
		{
			auto& upgradeSystem = bm::BMServiceLocator::GetUpgradeSystem();
			upgradeSystem.AddUpgrade(m_Type);
			GetOwner().FlagForDeletion();
		}
	}
}
