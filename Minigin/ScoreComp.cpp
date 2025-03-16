//---------------------------
// Include Files
//---------------------------
#include "ScoreComp.h"
#include "sdbmHash.h"

ScoreComp::ScoreComp(dae::GameObject& parent)
	:Component(parent)
	, m_ScoreChangedEvent{std::make_unique<Subject>(this)}
{
}

void ScoreComp::AddScore(int amount)
{
	m_Score += amount;
	m_ScoreChangedEvent->NotifyObservers(Event(make_sdbm_hash("ScoreChanged")));
}

int ScoreComp::GetScore() const
{
	return m_Score;
}

Subject& ScoreComp::OnScoreChanged()
{
	return *m_ScoreChangedEvent;
}




