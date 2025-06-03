#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/*========================README==========================================================================

todo add info

GameObject Class

	=> All GameObjects come automatically with a transformComp	

========================================================================================================*/
#include <glm.hpp>
#include <memory>
#include <vector>
#include <string>
#include <type_traits>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <format>

#include "sdbmHash.h"

namespace dae
{
	class Component;
	class TransformComp;
	class Scene;

	using gameobject_id = unsigned int;

	struct GobjID
	{
		const std::string_view name;
		const gameobject_id id;

		template <size_t N>
		constexpr GobjID(const char(&name)[N])
			:name{ name }
			, id{ make_sdbm_hash(name) }
		{
		}
	};

	class GameObject final
	{
	public:

		GameObject(const GobjID& name = {"___"});
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
		void UpdateImGui();

		template<typename compType>
		compType* GetComponent() const	//never returns nullptr, will throw instead
		{
			compType* pComponent = TryGetComponent<compType>();
			if (pComponent == nullptr)
			{
				std::cout << std::format("GameObject ({}) does not own a {}\n", GetName(), typeid(compType).name());
				throw std::logic_error(std::string("GameObject does not own a ") + typeid(compType).name());
			}

			return pComponent;
		}

		template<typename compType>
		compType* TryGetComponent() const	//allows nullptr as a valid return
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
		compType* AddComponent(compArgs&&... args)
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			static_assert(!std::is_same<compType, TransformComp>::value, "GameObject always has a TransformComp, no need to add it separatly");
			static_assert(std::is_constructible<compType, GameObject&, compArgs...>::value, "Invalid constructor arguments for compType");
			assert(TryGetComponent<compType>() == nullptr && "Duplicate components are not allowed on the same GameObject (or derive from the same parent component)");
			//assert(&(comp->GetOwner()) == this && "Attempted to add component that didn't set the owner to the correct GameObject");

			m_Components.emplace_back(std::make_unique<compType>(*this, std::forward<compArgs>(args)...));
			
			return static_cast<compType*>(m_Components.back().get());
		}

		template<typename compType>
		bool RemoveComponent()	//returns true if a component has been removed
		{
			static_assert(std::is_base_of<Component, compType>::value, "compType must derive of Component");
			static_assert(!std::is_same<compType, TransformComp>::value, "Cannot remove TransformComp from a GameObject");

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

		//id related======================================================
		std::string_view GetName() const;

		//deletion========================================================
		void FlagForDeletion();
		bool IsFlaggedForDeletion() const;

		//gameobject parent/children functions (public)===================
		void SetParent(GameObject* parent, bool keepWorldPos = true);
		GameObject* GetParent() const;
		const std::vector<GameObject*>& GetChildren();
		int GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		bool HasChild(GameObject* parent) const;

		//world position==================================================
		const glm::vec2& GetWorldPos();
		void InvalidateWorldPos();

		//local position==================================================
		const glm::vec2& GetLocalPosition();
		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalPosition(float x, float y);

		//Scene===========================================================
		Scene& GetScene();

		static constexpr std::string_view s_NullName{"___"};

	private:
		
		//====================
		//gameobject parent/children functions (private)
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		//world position
		const glm::vec2& CalculateWorldPos();

		//====================
		//set the parent scene (should only be called by the scene itself)
		friend class Scene;
		void SetScene(Scene* scene);

		//====================================================
		//id related
		GobjID m_Id;

		//====================
		//deletion
		bool m_FlaggedForDeletion = false;

		//====================
		//components variables
		std::vector<std::unique_ptr<Component>> m_Components;
		TransformComp* m_TransformComp{};
		bool m_IsCompFlaggedForDeletion{ false };

		//====================
		//gameobject parent/children variables
		std::vector<GameObject*> m_ChildrenGameObj{};
		GameObject* m_pParentGameObj{};
		//world position
		glm::vec2 m_WorldPos{};
		bool m_IsWorldPosValid{};

		//====================
		//scene of the gameobject
		Scene* m_pScene{};
	};
}

#endif // GAMEOBJECT_H