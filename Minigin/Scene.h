#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "SceneManager.h"
#include "GameObject.h"
#include "GameObjectHandle.h"

namespace dae
{
	//class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		GameObject* Add(std::unique_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Start();
		void FixedUpdate(float deltaFixedTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;
		void UpdateImGui();

		std::vector<GameObjectHandle> GetObjectByID(GobjID id) const;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_idCounter; 

		bool m_HasStarted{ false };	//if start() has ben called, Add() will cal start() instead
	};

}

#endif // SCENE_H