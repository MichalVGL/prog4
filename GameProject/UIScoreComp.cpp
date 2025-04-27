//---------------------------
// Include Files
//---------------------------
#include <cassert>
#include "UIScoreComp.h"
#include "sdbmHash.h"
#include "ScoreComp.h"
#include "TextComp.h"

UIScoreComp::UIScoreComp(dae::GameObject& parent, ScoreComp* compToObserve)
	:Component(parent)
{
	compToObserve->OnScoreChanged().AddObserver(this);
}

void UIScoreComp::Start()
{
	m_pTextComp = GetOwnerComponent<dae::TextComp>();
	m_pTextComp->SetText("Score: 0");
}

void UIScoreComp::Notify(dae::Event event, Component* comp)
{
	assert(comp != nullptr && "comp should not be nullptr here");

	switch (event.id)
	{
	case (dae::make_sdbm_hash("ScoreChanged")):
		assert(dynamic_cast<ScoreComp*>(comp) != nullptr && "Error in notify of UIScoreComp, wrong component given to event (needs ScoreComp with event \"ScoreChanged\")");
		auto* scoreComp = static_cast<ScoreComp*>(comp);
		m_pTextComp->SetText("Score: " + std::to_string(scoreComp->GetScore()));
		break;
	}
}




