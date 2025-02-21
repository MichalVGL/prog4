#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"

class TextComp;

//-----------------------------------------------------
// FPSComp Class									
//-----------------------------------------------------
class FPSComp final : public Component	//Args: float refreshPeriod
{
public:
	FPSComp(dae::GameObject& parent, float refeshPeriod = 1.f);				// Constructor
	~FPSComp() override;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	FPSComp(const FPSComp& other)					= delete;
	FPSComp(FPSComp&& other) noexcept				= delete;
	FPSComp& operator=(const FPSComp& other)		= delete;
	FPSComp& operator=(FPSComp&& other)	noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void Start() override;

	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;


private: 

	TextComp* m_pTextComp;

	float m_RefreshPeriod;
	float m_RefreshCounter;
	float m_FPS;
};

 
