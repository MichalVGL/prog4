//---------------------------
// Include Files
//---------------------------
#include <cassert>
#include "UIHealthComp.h"
#include "sdbmHash.h"
#include "HealthComp.h"
#include "TextComp.h"

UIHealthComp::UIHealthComp(dae::GameObject& parent, HealthComp* compToObserve)
	:Component(parent)
{
	compToObserve->OnKilled().AddObserver(this);
}

void UIHealthComp::Start()
{
	m_pTextComp = GetOwnerComponent<TextComp>();
	m_pTextComp->SetText("# lives: 3");	//hardcoded for now due to uncertainties/crashes due to initialization/start order 
}


void UIHealthComp::Notify(Event event, Component* comp)
{
	assert(comp != nullptr && "comp should not be nullptr here");

	switch (event.id)
	{
	case (make_sdbm_hash("HealthChanged")):
		assert(dynamic_cast<HealthComp*>(comp) != nullptr && "Error in notify of UIScoreComp, wrong component given to event (needs ScoreComp with event \"ScoreChanged\")");
		auto* healtComp = static_cast<HealthComp*>(comp);
		m_pTextComp->SetText("# lives: " + std::to_string(healtComp->GetCurrentLives()));
		break;
	}
}




