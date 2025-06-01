//---------------------------
// Include Files
//---------------------------
#include <ServiceLocator.h>

#include "ScoreComp.h"

ScoreComp::ScoreComp(dae::GameObject& parent)
	:Component(parent)
	, m_ScoreChangedEvent{std::make_unique<dae::Subject>(this)}
{
}

void ScoreComp::AddScore(int amount)
{
	m_Score += amount;
	m_ScoreChangedEvent->NotifyObservers(dae::Event(dae::make_sdbm_hash("ScoreChanged")));

	m_ScoreChangedSoundToken.Play();
}

int ScoreComp::GetScore() const
{
	return m_Score;
}

dae::Subject& ScoreComp::OnScoreChanged()
{
	return *m_ScoreChangedEvent;
}




