#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"
#include "Component.h"
#include "RenderComp.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//virtual void Update();	todo delete temp code
		//virtual void Render() const;

		void FixedUpdate(float deltaFixedTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		template<typename compType>
		std::shared_ptr<compType> GetComponent() const
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

			for (auto& comp : m_Components)
			{
				if (auto compCheck{ dynamic_pointer_cast<compType>(comp) }; compCheck != nullptr)
				{
					return compCheck;
				}
			}
			return nullptr;
		}

		template<typename compType>
		std::shared_ptr<compType> AddComponent(compType comp)
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

			m_Components.push_back(std::make_shared<compType>(std::move(comp)));
			
			//return static_cast<compType*>(m_Components.back().get());
			return std::dynamic_pointer_cast<compType>(m_Components.back());
		}

		template<typename compType>	//todo test code
		bool RemoveComponent()	//returns true if a component has been removed
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");

			auto loc = std::find_if(m_Components.begin(), m_Components.end(), [](const std::shared_ptr<Component>& comp) {
				return std::dynamic_pointer_cast<compType>(comp) != nullptr;
				});
			if (loc != m_Components.end())
			{
				m_Components.erase(loc);
				return true;
			}
			else
			{
				return false;
			}
		}

	private:

		std::vector<std::shared_ptr<Component>> m_Components;
	};
}
