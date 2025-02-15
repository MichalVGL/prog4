#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"

//-----------------------------------------------------
// FPSComp Class									
//-----------------------------------------------------
class FPSComp final : public Component
{
public:
	FPSComp(dae::GameObject& parent, float refeshPeriod = 1.f);				// Constructor
	~FPSComp() override;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	FPSComp(const FPSComp& other)					= default;
	FPSComp(FPSComp&& other) noexcept				= default;
	FPSComp& operator=(const FPSComp& other)		= default;
	FPSComp& operator=(FPSComp&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;


private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------

	float m_RefreshPeriod;
	float m_RefreshCounter;
	float m_FPS;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	
};

 
