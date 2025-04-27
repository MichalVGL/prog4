#ifndef UISCORECOMP_H
#define UISCORECOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <IObserver.h>
#include <Component.h>
#include <Event.h>

//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------
namespace dae
{
	class TextComp;
}
class ScoreComp;

class UIScoreComp final : public dae::Component, public dae::IObserver 	//Args: GameObject& parent, HealthComp* compToObserve
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

	void Notify(dae::Event event, Component* comp) override;

private: 

	dae::TextComp* m_pTextComp{};

};

#endif // !UISCORECOMP_H