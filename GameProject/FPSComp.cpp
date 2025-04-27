//---------------------------
// Include Files
//---------------------------

#include <format>
#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"

//---------------------------
// Constructor & Destructor
//---------------------------

FPSComp::FPSComp(dae::GameObject& parent, float refeshPeriod)
	:Component{ parent }
	, m_pTextComp{}
	, m_RefreshPeriod{ refeshPeriod }
	, m_RefreshCounter{}
	, m_FPS{}
{
}

void FPSComp::Start()
{
	m_pTextComp = GetOwnerComponent<dae::TextComp>();
}

void FPSComp::Update(float deltaTime)
{
	if( (m_RefreshCounter += deltaTime) > m_RefreshPeriod )
	{
		m_FPS = 1.f / deltaTime;

		m_pTextComp->SetText(std::format("{:.2f}", m_FPS));

		m_RefreshCounter = 0.f;
	}
}




