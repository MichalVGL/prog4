#pragma once	//todo change to header guards in new files/template files
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include "Component.h"
#include "Subject.h"

//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------


class /*Component_Name*/HealthComp final : public Component	//Args: int maxLives
{
public:
	HealthComp(dae::GameObject& parent, int maxLives);	

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	HealthComp(const HealthComp& other)						= default;
	HealthComp(HealthComp&& other) noexcept					= default;
	HealthComp& operator=(const HealthComp& other)			= default;
	HealthComp& operator=(HealthComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	bool Damage();

	int GetCurrentLives() const;

	Subject& OnKilled();

private: 

	int m_MaxLives;
	int m_CurrentLives;

	std::unique_ptr<Subject> m_DamagedEvent;

};

 
