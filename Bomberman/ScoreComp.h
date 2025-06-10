#ifndef SCORECOMP_H
#define SCORECOMP_H

#include "Component.h"


namespace bm
{
	class ScoreComp final : public dae::Component	//Args: int score
	{
	public:
		ScoreComp(dae::GameObject& parent, int score);

		ScoreComp(const ScoreComp& other) = default;
		ScoreComp(ScoreComp&& other) noexcept = default;
		ScoreComp& operator=(const ScoreComp& other) = default;
		ScoreComp& operator=(ScoreComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		void OnDestroy() override;
		//--------------------------



	private:

		static constexpr int s_TextSize{ 10 };
		static constexpr float s_DisplayTextTime{ 4.f };

		const int m_ScoreAmount;

	};
}
#endif // !SCORECOMP_H