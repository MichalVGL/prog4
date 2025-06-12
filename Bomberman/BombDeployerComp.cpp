#include "BombDeployerComp.h"

#include "BMServiceLocator.h"
#include "BombComp.h"

bm::BombDeployerComp::BombDeployerComp(dae::GameObject& parent)
	:Component(parent)
{
	m_Bombs.reserve(3);
}

void bm::BombDeployerComp::DeployBomb()
{
	ValidateBombHandles();

	//check if you are allowed to deploy a bomb
	auto& upgradeSystem = bm::BMServiceLocator::GetUpgradeSystem();
	if (static_cast<int>(m_Bombs.size()) >= upgradeSystem.GetMaxBombs())
	{
		return;
	}

	//deploy the bomb
	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	m_Bombs.emplace_back(spawnSystem.SpawnBomb(GetOwner().GetWorldPos()));

	//sound
	auto& levelSoundsPlayer = bm::BMServiceLocator::GetLevelSoundsPlayer();
	levelSoundsPlayer.PlaySound(bm::LevelSound::bombDeployed);
}

void bm::BombDeployerComp::DetonateLastBomb()
{
	ValidateBombHandles();
	
	if (m_Bombs.empty())
	{
		return;	//no bombs to detonate
	}

	auto& upgradeSystem = bm::BMServiceLocator::GetUpgradeSystem();
	if (upgradeSystem.IsRemoteActive() == false)
		return;	

	m_Bombs.back()->GetComponent<bm::BombComp>()->Detonate();
}

//Private===========================================

void bm::BombDeployerComp::ValidateBombHandles()
{
	m_Bombs.erase(std::remove_if(m_Bombs.begin(), m_Bombs.end(),
		[](dae::GameObjectHandle& handle) { return handle.Get() == nullptr; }), m_Bombs.end());
}



//==============================================================
// Commands
//==============================================================

//DeployBomb
bm::DeployCommand::DeployCommand(dae::GameObject& gObj)
{
	m_BombDeployerComp.Init(gObj);
}

void bm::DeployCommand::Execute()
{
	m_BombDeployerComp->DeployBomb();
}

//DetonateBomb
bm::DetonateCommand::DetonateCommand(dae::GameObject& gObj)
{
	m_BombDeployerComp.Init(gObj);
}

void bm::DetonateCommand::Execute()
{
	m_BombDeployerComp->DetonateLastBomb();
}
