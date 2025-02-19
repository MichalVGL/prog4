#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <glm.hpp>
#include "Component.h"

//-----------------------------------------------------
// TransformComp Class									
//-----------------------------------------------------
class TransformComp final : public Component
{
public:
	TransformComp(dae::GameObject& parent);				// Constructor
	~TransformComp() override;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	TransformComp(const TransformComp& other)					= delete;
	TransformComp(TransformComp&& other) noexcept				= delete;
	TransformComp& operator=(const TransformComp& other)		= delete;
	TransformComp& operator=(TransformComp&& other)	noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;

	const glm::vec2& GetPosition() const;
	void SetPosition(float x, float y);

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	glm::vec2 m_Position;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	
};

 
