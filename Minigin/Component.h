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
	virtual ~Component() = 0;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Component(const Component& other)					= delete;
	Component(Component&& other) noexcept				= delete;
	Component& operator=(const Component& other)		= delete;
	Component& operator=(Component&& other)	noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	virtual void Start();
	virtual void FixedUpdate(float deltaFixedTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);

	virtual void Render() const {};

	void FlagForDeletion();
	bool IsFlaggedForDeletion() const;

	const dae::GameObject& GetOwner() const;

private: 

	bool m_IsFlaggedForDeletion;
	const dae::GameObject& m_GObjectParent;
};

 
