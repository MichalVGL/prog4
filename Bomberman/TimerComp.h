#ifndef TIMERCOMP_H
#define TIMERCOMP_H

#include "Component.h"

#include <functional>
#include <format>

#include <EngineComponents.h>

namespace bm
{
	class TimerComp final : public dae::Component	//Args: float startTime, bool useText = true
	{
	public:
		TimerComp(dae::GameObject& parent, float startTime, bool useText = true);

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
		//possible functions if needed later
		//void SetTime();
		//void Reset();

		void SetFormatFunction(std::function<std::string(float)> func);

	private:

		dae::OptComp<dae::TextComp> m_TextComp;
		bool m_UseText;

		float m_RemainingTime;
		bool m_Complete{ false };

		std::function<std::string(float)> m_FormatFunc{ [](float t) {return std::format("{:.2f}", t); } };

	};
}
#endif // !TIMERCOMP_H