#include "TimerComp.h"

bm::TimerComp::TimerComp(dae::GameObject& parent, float startTime, bool useText)
	:Component(parent)
	, m_UseText{ useText }
	, m_RemainingTime{ startTime }
{
	if (startTime < 0.f)
		m_Complete = true;
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
			m_TimerCompleteSubject.NotifyObservers();
		}
		if (m_TextComp)
			m_TextComp->SetText(m_FormatFunc(m_RemainingTime));
	}
}

float bm::TimerComp::RemainingTime()
{
	return m_RemainingTime;
}

bool bm::TimerComp::IsComplete()
{
	return m_Complete;
}

void bm::TimerComp::SetTime(float time)
{
	if (time > 0.f)
	{
		m_RemainingTime = time;
		m_Complete = false;
	}
}

void bm::TimerComp::SetFormatFunction(std::function<std::string(float)> func)
{
	m_FormatFunc = std::move(func);
}

dae::Subject& bm::TimerComp::OnTimerComplete()
{
	return m_TimerCompleteSubject;
}
