#ifndef TRANSFORMCOMP_H
#define TRANSFORMCOMP_H

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
	TransformComp(dae::GameObject& parent);

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	TransformComp(const TransformComp& other)					= delete;
	TransformComp(TransformComp&& other) noexcept				= delete;
	TransformComp& operator=(const TransformComp& other)		= delete;
	TransformComp& operator=(TransformComp&& other)	noexcept	= delete;

	// -------------------------
	// Base Functions
	// -------------------------  
	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//--------------------------

	const glm::vec2& GetLocalPosition() const;
	void SetLocalPosition(float x, float y);
	void SetLocalPosition(const glm::vec2& newPos);

private: 

	glm::vec2 m_Position;

};

 
#endif // TRANSFORMCOMP_H