#ifndef UISCORECOMP_H
#define UISCORECOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "Component.h"
#include "Observer.h"
#include "Event.h"

//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------
class ScoreComp;
class TextComp;

class UIScoreComp final : public Component, public IObserver 	//Args: 
{
public:
	UIScoreComp(dae::GameObject& parent, ScoreComp* compToObserve);	

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	UIScoreComp(const UIScoreComp& other)						= default;
	UIScoreComp(UIScoreComp&& other) noexcept					= default;
	UIScoreComp& operator=(const UIScoreComp& other)			= default;
	UIScoreComp& operator=(UIScoreComp&& other) noexcept		= default;

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

#endif // !UISCORECOMP_H