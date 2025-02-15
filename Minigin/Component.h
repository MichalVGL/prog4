#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------

//-----------------------------------------------------
// Forward Declarations
//-----------------------------------------------------

namespace dae
{
	class GameObject;
}

//-----------------------------------------------------
// Component Class									
//-----------------------------------------------------
class Component
{
public:
	Component(dae::GameObject& parent);		// Constructor
	Component() = delete;				
	virtual ~Component() = 0;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Component(const Component& other)					= default;
	Component(Component&& other) noexcept				= default;
	Component& operator=(const Component& other)		= default;
	Component& operator=(Component&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	virtual void FixedUpdate(float deltaFixedTime) { deltaFixedTime; };
	virtual void Update(float deltaTime) { deltaTime; };
	virtual void LateUpdate(float deltaTime) { deltaTime; };

	virtual void Render() const {};

protected:

	const dae::GameObject& m_GObjectParent;

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

};

 
