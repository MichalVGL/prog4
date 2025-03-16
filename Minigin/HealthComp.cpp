//---------------------------
// Include Files
//---------------------------
#include "HealthComp.h"
#include "sdbmHash.h"

HealthComp::HealthComp(dae::GameObject& parent, int maxLives)
	:Component(parent)
	, m_MaxLives{maxLives}
	, m_CurrentLives{maxLives}
	, m_DamagedEvent{std::make_unique<Subject>(this)}
{
}

bool HealthComp::Damage()
{
 	--m_CurrentLives;
	m_DamagedEvent->NotifyObservers(Event(make_sdbm_hash("HealthChanged")));
	if (m_CurrentLives <= 0)
	{
		//GetOwner().FlagForDeletion();	//todo determine health behaviour
	}
	return false;
}

int HealthComp::GetCurrentLives() const
{
	return m_CurrentLives;
}

Subject& HealthComp::OnKilled()
{
	return *m_DamagedEvent;
}
