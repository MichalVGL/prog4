#ifndef COMPONENT_H
#define COMPONENT_H


/*========================README==========================================================================

Base Component Class

	=>

//todo 
//SubComponent creation
//Component creation in the gameobject
//debug only checks (duplicate components,...)

========================================================================================================*/
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

namespace dae
{
	class Component
	{
	public:

		// Constructor is protected
		Component() = delete;
		virtual ~Component() = default;

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other)	noexcept = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------

		virtual void Start();
		virtual void FixedUpdate(float deltaFixedTime);
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void UpdateImGui();

		virtual void Render() const;

		void FlagForDeletion();
		bool IsFlaggedForDeletion() const;

		dae::GameObject& GetOwner() const;

		template<typename compType>
		compType* GetOwnerComponent()	//doesn't allow nullptr as valid return (but only checks in debug mode)
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

		template<typename compType>
		compType* TryGetOwnerComponent()	//allows nullptr as valid return
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

			return GetOwner().GetComponent<compType>();
		}

	protected:

		Component(dae::GameObject& parent);	//protected to make sure this class cannot be created outside of derived classes

	private:

		bool m_IsFlaggedForDeletion;
		dae::GameObject& m_GObjectParent;
	};
}

#endif // !COMPONENT_H