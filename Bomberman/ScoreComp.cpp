#include "ScoreComp.h"

#include "BMServiceLocator.h"

bm::ScoreComp::ScoreComp(dae::GameObject& parent, int score)
	:Component{ parent }
	, m_ScoreAmount{ score }
{
}

void bm::ScoreComp::OnDestroy()
{
	//add the score
	auto& scoreSystem = BMServiceLocator::GetScoreSystem();
	scoreSystem.AddScore(m_ScoreAmount);

	//spawn text
	auto& spawnSystem = BMServiceLocator::GetSpawnSystem();
	spawnSystem.SpawnTempText(GetOwner().GetWorldPos(), std::to_string(m_ScoreAmount), s_DisplayTextTime, s_TextSize);
}
