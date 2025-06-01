#ifndef HEALTHCOMP_H
#define HEALTHCOMP_H

#include <memory>

#include <Sound.h>

#include "Component.h"
#include "Subject.h"

class HealthComp final : public dae::Component	//Args: int maxLives
{
public:
	HealthComp(dae::GameObject& parent, int maxLives);	

	HealthComp(const HealthComp& other)						= default;
	HealthComp(HealthComp&& other) noexcept					= default;
	HealthComp& operator=(const HealthComp& other)			= default;
	HealthComp& operator=(HealthComp&& other) noexcept		= default;

	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	bool Damage();

	int GetCurrentLives() const;

	dae::Subject& OnKilled();

private: 

	int m_MaxLives;
	int m_CurrentLives;

	std::unique_ptr<dae::Subject> m_DamagedEvent;
	dae::SoundToken m_DamageSoundToken{m_DamageSoundEntry};

	static constexpr dae::SoundEntry m_DamageSoundEntry{ "TestSounds/Bomberman SFX (3).wav" };
};

#endif // !HEALTHCOMP_H