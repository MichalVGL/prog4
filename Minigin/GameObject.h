#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"
//#include "Component.h"
#include "RenderComp.h"	//todo delete #include when handing in (only needed for intellisense template param)

class Component;

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

		template<typename compType>
		compType* AddComponent(std::unique_ptr<compType>&& comp)
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			assert(GetComponent<compType>() == nullptr && "Duplicate components are not allowed on the same GameObject");
			assert(&(comp->GetOwner()) == this && "Attempted to add component that didn't set the owner to the correct GameObject");	//todo check this doesnt throw an error

			m_Components.push_back(std::move(comp));
			
			return static_cast<compType*>(m_Components.back().get());
		}

		template<typename compType>
		bool RemoveComponent()	//returns true if a component has been removed
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

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

	private:

		std::vector<std::unique_ptr<Component>> m_Components;

		bool m_IsCompFlaggedForDeletion;

	};
}
