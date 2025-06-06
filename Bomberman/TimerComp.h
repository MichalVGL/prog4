#ifndef TIMERCOMP_H
#define TIMERCOMP_H

#include "Component.h"

#include <functional>
#include <format>

#include <EngineComponents.h>
#include <Subject.h>

namespace bm
{
	class TimerComp final : public dae::Component	//Args: float startTime = -1.f, bool useText = true
	{
	public:
		TimerComp(dae::GameObject& parent, float startTime = -1.f, bool useText = true);

		TimerComp(const TimerComp& other) = default;
		TimerComp(TimerComp&& other) noexcept = default;
		TimerComp& operator=(const TimerComp& other) = default;
		TimerComp& operator=(TimerComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		float RemainingTime();
		bool IsComplete();
		//possible functions if needed later
		void SetTime(float time);
		//void Reset();

		void SetFormatFunction(std::function<std::string(float)> func);

		dae::Subject& OnTimerComplete();

		static constexpr dae::Event s_TimerCompleteEvent{ "TimerComplete" };

	private:

		dae::OptComp<dae::TextComp> m_TextComp;
		bool m_UseText;

		float m_RemainingTime;
		bool m_Complete{ false };
		dae::Subject m_TimerCompleteSubject{ s_TimerCompleteEvent };

		std::function<std::string(float)> m_FormatFunc{ [](float t) {return std::format("{:.2f}", t); } };

	};
}
#endif // !TIMERCOMP_H