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
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:

		// Constructor is protected
		Component() = delete;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other)	noexcept = delete;

		virtual void Start();
		virtual void FixedUpdate(float deltaFixedTime);
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		virtual void UpdateImGui();

		virtual void OnDestroy();	// called form the gameobject when the gameobject is flagged for deletion. (but not regular destructor!!!)

		virtual void Render() const;

		void FlagForDeletion();
		bool IsFlaggedForDeletion() const;

		GameObject& GetOwner() const;

		template<typename compType>
		compType* GetOwnerComponent()	//doesn't allow nullptr as valid return (but only checks in debug mode)
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			return GetOwner().GetComponent<compType>();
		}

		template<typename compType>
		compType* TryGetOwnerComponent()	//allows nullptr as valid return
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			return GetOwner().TryGetComponent<compType>();
		}

	protected:

		Component(GameObject& parent);	//protected to make sure this class cannot be created outside of derived classes

	private:

		bool m_IsFlaggedForDeletion;
		GameObject& m_GObjectParent;
	};

	//=====================================================================================================================================================================
	//=====================================================================================================================================================================
	//=====================================================================================================================================================================

	template<typename CompType>
	class ReqComp final
	{
	public:
		ReqComp()
		{
			static_assert(std::is_base_of<Component, CompType>::value, "CompType must derive of Component");
		}
		~ReqComp() = default;
		ReqComp(const ReqComp& other) = delete;
		ReqComp(ReqComp&& other) noexcept = delete;
		ReqComp& operator=(const ReqComp& other) = delete;
		ReqComp& operator=(ReqComp&& other)	noexcept = delete;

		CompType* Init(GameObject& parent)
		{
#ifdef _DEBUG
			try
			{
				m_pComponent = parent.GetComponent<CompType>();
			}
			catch (const std::logic_error& e)
			{
				throw std::logic_error(std::string("ReqComp<") + typeid(CompType).name() + "> initialization failed: " + e.what());
			}
#else
			m_pComponent = parent.GetComponent<CompType>();
#endif // _DEBUG
			return m_pComponent;
		}

		CompType* Init(CompType* comp)	//can throw std::logic_error if the gObj doesnt have the component
		{
			if (comp == nullptr)
			{
				throw std::logic_error(std::string("ReqComp<") + typeid(CompType).name() + "> initialization failed: nullptr passed");
			}
			m_pComponent = comp;
			return m_pComponent;
		}

		CompType* operator->() { return m_pComponent; }

	private:
		CompType* m_pComponent{ nullptr };
	};

	template<typename CompType>
	class OptComp final
	{
	public:
		OptComp()
		{
			static_assert(std::is_base_of<Component, CompType>::value, "CompType must derive of Component");
		}
		~OptComp() = default;
		OptComp(const OptComp& other) = delete;
		OptComp(OptComp&& other) noexcept = delete;
		OptComp& operator=(const OptComp& other) = delete;
		OptComp& operator=(OptComp&& other)	noexcept = delete;

		CompType* Init(GameObject& parent)
		{
			m_pComponent = parent.TryGetComponent<CompType>();

			return m_pComponent;
		}

		CompType* operator->() { return m_pComponent; }

		operator bool() const noexcept { return m_pComponent != nullptr; }	//for if statements (or any bool usage...)

	private:
		CompType* m_pComponent{ nullptr };
	};
}

#endif // !COMPONENT_H