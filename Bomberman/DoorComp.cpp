#include "DoorComp.h"

#include <ServiceLocator.h>

#include "BMGameDefines.h"

bm::DoorComp::DoorComp(dae::GameObject& parent)
	:Component(parent), TileMod{parent, DOOR_MODID}
{
}

void bm::DoorComp::Start()
{
	m_RenderComp.Init(GetOwner());
	m_RenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	m_RenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	m_RenderComp->LoadImageTexture(s_DoorTextureEntry);

	m_TileCollisionComp.Init(GetOwner());
	m_TileCollisionComp->AddTarget(PLAYER_GOBJID);
	m_TileCollisionComp->OnCollision().AddObserver(this);

	m_Enemies = dae::ServiceLocator::GetSceneSystem().GetCurrentScene()->GetObjectsByID(ENEMY_GOBJID);
}

void bm::DoorComp::Update(float)
{
	if (m_DoorOpen == false)
	{
		m_Enemies.erase(std::remove_if(m_Enemies.begin(), m_Enemies.end(),
			[](dae::GameObjectHandle& handle)
			{return handle.Get() == nullptr; }), m_Enemies.end());

		if (m_Enemies.empty())
		{
			m_DoorOpen = true;
			m_DoorOpenSoundToken.Play();
		}
	}
}

bool bm::DoorComp::IsWalkable() const
{
	return true;
}

void bm::DoorComp::Notify(dae::Event event, const std::any&)
{
	if (event == TileCollisionComp::s_CollisionEvent)
	{
		if (m_DoorOpen)
		{
			m_PlayerEscapedSubject.NotifyObservers();
		}
	}
}

dae::Subject& bm::DoorComp::OnPlayerEscaped()
{
	return m_PlayerEscapedSubject;
}
