#include "TimerComp.h"

bm::TimerComp::TimerComp(dae::GameObject& parent, float startTime, bool useText)
	:Component(parent)
	, m_UseText{ useText }
	, m_RemainingTime{ startTime }
{
	if (startTime < 0.f)
		std::cout << std::format("Warning: negative startTime set on timercomp. [Gameobject: {}]\n", GetOwner().GetName());
}

void bm::TimerComp::Start()
{
	if (m_UseText)
		m_TextComp.Init(GetOwner());
}

void bm::TimerComp::Update(float deltaTime)
{
	if (!m_Complete)
	{
		m_RemainingTime -= deltaTime;
		if (m_RemainingTime < 0.f)
		{
			m_Complete = true;
			m_RemainingTime = 0.f;
		}
		if (m_TextComp)
			m_TextComp->SetText(m_FormatFunc(m_RemainingTime));
	}
}

float bm::TimerComp::RemainingTime()
{
	return m_RemainingTime;
}

void bm::TimerComp::SetFormatFunction(std::function<std::string(float)> func)
{
	m_FormatFunc = std::move(func);
}
