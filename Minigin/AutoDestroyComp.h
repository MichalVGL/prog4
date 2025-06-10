#ifndef AUTODESTROYCOMP_H
#define AUTODESTROYCOMP_H

#include "Component.h"

namespace dae
{
	class AutoDestroyComp final : public dae::Component	//Args: float timeToDestroy
	{
	public:
		AutoDestroyComp(dae::GameObject& parent, float timeToDestroy);

		AutoDestroyComp(const AutoDestroyComp& other) = default;
		AutoDestroyComp(AutoDestroyComp&& other) noexcept = default;
		AutoDestroyComp& operator=(const AutoDestroyComp& other) = default;
		AutoDestroyComp& operator=(AutoDestroyComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------



	private:

		float m_TimeRemaining;

	};
}
#endif // !AUTODESTROYCOMP_H