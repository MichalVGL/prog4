#pragma once
#include <memory>
#include <vector>
#include <string>
#include <type_traits>
#include <utility>
#include "Transform.h"
#include "RenderComp.h"	//todo delete #include when handing in (only needed for intellisense template param)
//#include "TransformComp.h"  //delete this aswell

class Component;

//==============General GameObject Info========================
/*
All GameObjects come automatically with a transformComp
*/

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Start();
		void FixedUpdate(float deltaFixedTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		template<typename compType>
		compType* GetComponent() const
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

			for (const auto& comp : m_Components)
			{
				if (compType* compCheck = dynamic_cast<compType*>(comp.get()); compCheck != nullptr)
				{
					return compCheck;
				}
			}
			return nullptr;
		}

		template<typename compType, typename... compArgs>
		compType* AddComponent(compArgs... args)
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			static_assert(std::is_same<compType, TransformComp>::value == false, "GameObject always has a TransformComp, no need to add it seperatly");
			static_assert(std::is_constructible<compType, GameObject&, compArgs...>::value, "Invalid constructor arguments for compType");
			assert(GetComponent<compType>() == nullptr && "Duplicate components are not allowed on the same GameObject");
			//assert(&(comp->GetOwner()) == this && "Attempted to add component that didn't set the owner to the correct GameObject");	//todo check this doesnt throw an (false) error

			m_Components.push_back(std::make_unique<compType>(*this, std::forward<compArgs>(args)...));
			
			return static_cast<compType*>(m_Components.back().get());
		}
		
		//old version
		
		//template<typename compType>
		//compType* AddComponent(std::unique_ptr<compType>&& comp)
		//{
		//	static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
		//	static_assert(std::is_same<compType, TransformComp>::value == false, "GameObject always has a TransformComp, no need to add it seperatly");
		//	assert(GetComponent<compType>() == nullptr && "Duplicate components are not allowed on the same GameObject");
		//	assert(&(comp->GetOwner()) == this && "Attempted to add component that didn't set the owner to the correct GameObject");	//todo check this doesnt throw an (false) error
		//
		//	m_Components.push_back(std::move(comp));
		//
		//	return static_cast<compType*>(m_Components.back().get());
		//}

		template<typename compType>
		bool RemoveComponent()	//returns true if a component has been removed
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			static_assert(std::is_same<compType, TransformComp>::value == false, "Cannot remove TransformComp from a GameObject");

			auto loc = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& comp) {
				return dynamic_cast<compType*>(comp.get()) != nullptr;
				});
			if (loc != m_Components.end())
			{
				(*loc)->FlagForDeletion();
				m_IsCompFlaggedForDeletion = true;
				return true;
			}
			else
			{
				return false;
			}
		}

		void SetParent(GameObject* parent, bool keepWorldPos = true);
		GameObject* GetParent() const;
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		bool HasChild(GameObject* parent) const;

	private:

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		std::vector<std::unique_ptr<Component>> m_Components;

		bool m_IsCompFlaggedForDeletion;

		std::vector<GameObject*> m_ChildGameObjects;
		GameObject* m_pParentGameObject;

	};
}
