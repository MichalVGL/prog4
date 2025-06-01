//---------------------------
// Include Files
//---------------------------
#include <sdbmHash.h>

#include <ServiceLocator.h>

#include "HealthComp.h"

HealthComp::HealthComp(dae::GameObject& parent, int maxLives)
	:Component(parent)
	, m_MaxLives{maxLives}
	, m_CurrentLives{maxLives}
	, m_DamagedEvent{std::make_unique<dae::Subject>(this)}
{
}

bool HealthComp::Damage()
{
 	--m_CurrentLives;

	m_DamageSoundToken.Play();

	m_DamagedEvent->NotifyObservers(dae::Event(dae::make_sdbm_hash("HealthChanged")));
	if (m_CurrentLives <= 0)
	{
		//GetOwner().FlagForDeletion();	
	}
	return false;
}

int HealthComp::GetCurrentLives() const
{
	return m_CurrentLives;
}

dae::Subject& HealthComp::OnKilled()
{
	return *m_DamagedEvent;
}
