#ifndef UIHEALTHCOMP_H
#define UIHEALTHCOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <Component.h>
#include <IObserver.h>
#include <Event.h>


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------
namespace dae
{
	class TextComp;
}
class HealthComp;

class UIHealthComp final : public dae::Component, public dae::IObserver	//Args: HealthComp* compToObserve
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

	void Notify(dae::Event event, Component* comp) override;

private: 

	dae::ReqComp<dae::TextComp> m_TextComp{};

};

#endif // !UIHEALTHCOMP_H