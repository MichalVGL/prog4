#ifndef SCENESSCRIPT_H
#define SCENESSCRIPT_H

#include <vector>
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Scene
	{
	public:

		Scene();

		virtual ~Scene() = default;

		virtual void Load() = 0;
		virtual void Exit() = 0;
		virtual std::unique_ptr<Scene> UpdateScene(float deltaTime) = 0;

		GameObject* Add(std::unique_ptr<GameObject> object);
		void RemoveAll();

		std::vector<GameObjectHandle> GetObjectsByID(GobjID id) const;

		void UpdateHandles(std::vector<GameObjectHandle>& handles);	//use as a automatic nullptr check for all handles (will auto remove them from the vector)

	protected:

		virtual void OnObjectAdded(GameObjectHandle object) {};

		std::vector<std::unique_ptr<GameObject>> m_Objects{};

		static constexpr int s_MaxObjects{ 2000 };


	private:

		friend class Default_SceneSystem;

		void Start();
		void FixedUpdate(float deltaFixedTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;
		void UpdateImGui();

		void RemoveFlaggedObjects();
		void SortRenderObjects() const;


		mutable std::vector<const GameObject*> m_RenderSortedObjects{};
		mutable bool m_RenderSortedObjectsDirty{ true };

		bool m_HasStarted{ false };	//if start() has ben called, Add() will cal start() instead
	};
}

#endif // !SCENESSCRIPT_H
