#ifndef ROTATIONCOMP_H
#define ROTATIONCOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------

namespace dae
{
	class TransformComp;
}

//==========================================================================
//This component rotates this gameobject around the parent (using this gameObjects local position)
//==========================================================================

class RotationComp final : public dae::Component	//Args: float degr/s = 0.f
{
public:
	RotationComp(dae::GameObject& parent, float degreesPerSecond = 0.f);

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	RotationComp(const RotationComp& other)						= default;
	RotationComp(RotationComp&& other) noexcept					= default;
	RotationComp& operator=(const RotationComp& other)			= default;
	RotationComp& operator=(RotationComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	void SetRotationSpeed(float degreesPerSecond);

private: 

	dae::TransformComp* m_pTransformComp;

	float m_RadiansPerSecond;
	bool m_IsActive;	//if the rotation is set to 0 this will be false. To prevent spoiling the worldpos of the gameobject
};

 
#endif // ROTATIONCOMP_H