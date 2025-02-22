
/*========================README==========================================================================

todo add info here

========================================================================================================*/
#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <iostream>
#include <cassert>
#include "GameObject.h"
//-----------------------------------------------------
// Forward Declarations
//-----------------------------------------------------



//-----------------------------------------------------
// Component Class									
//-----------------------------------------------------
class Component
{
public:

	// Constructor is protected
	Component() = delete;
	virtual ~Component() = default;

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


protected:

	Component(dae::GameObject& parent);	//protected to make sure this class cannot be created outside of derived classes

	template<typename compType>
	compType* GetOwnerComponent()
	{
		static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
		
		compType* pComponent = GetOwner().GetComponent<compType>();

#ifdef _DEBUG
		if (pComponent == nullptr) 
		{
			std::cerr << "\nComponent error: Owner does not own a " << typeid(compType).name() << ", requested by " << typeid(*this).name() << '\n';
			assert(false);
		}
#endif // _DEBUG

		return pComponent;
	}

	dae::GameObject& GetOwner() const;

private: 

	bool m_IsFlaggedForDeletion;
	dae::GameObject& m_GObjectParent;
};