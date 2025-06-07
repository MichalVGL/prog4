#include "UpgradeSystem.h"

void bm::UpgradeSystem::AddUpgrade(UpgradeType type)
{
	switch (type)
	{
	case bm::UpgradeType::remoteDetonator:
		m_RemoteActive = true;
		break;
	case bm::UpgradeType::bombCount:
		m_MaxBombs++;
		break;
	case bm::UpgradeType::bombRange:
		m_BombRange++;
		break;
	}
}

void bm::UpgradeSystem::ResetUpgrades()
{
	m_MaxBombs = 1;
	m_BombRange = 1;
	m_RemoteActive = false;
}

int bm::UpgradeSystem::GetMaxBombs() const
{
	return m_MaxBombs;
}

int bm::UpgradeSystem::GetBombRange() const
{
	return m_BombRange;
}

bool bm::UpgradeSystem::IsRemoteActive() const
{
	return m_RemoteActive;
}
