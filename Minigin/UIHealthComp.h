#ifndef UIHEALTHCOMP_H
#define UIHEALTHCOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"
#include "Observer.h"
#include "Event.h"


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------
class HealthComp;
class TextComp;

class UIHealthComp final : public Component, public Observer	//Args: 
{
public:
	UIHealthComp(dae::GameObject& parent, HealthComp* compToObserve);

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	UIHealthComp(const UIHealthComp& other)						= default;
	UIHealthComp(UIHealthComp&& other) noexcept					= default;
	UIHealthComp& operator=(const UIHealthComp& other)			= default;
	UIHealthComp& operator=(UIHealthComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	void Notify(Event event, Component* comp) override;

private: 

	TextComp* m_pTextComp{};

};

#endif // !UIHEALTHCOMP_H