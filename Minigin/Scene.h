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

		virtual ~Scene() = default;

		virtual void Load() = 0;
		virtual void Exit() = 0;
		virtual std::unique_ptr<Scene> UpdateScene(float deltaTime) = 0;

		GameObject* Add(std::unique_ptr<GameObject> object);
		void RemoveAll();

		std::vector<GameObjectHandle> GetObjectByID(GobjID id) const;

	protected:

		std::vector<std::unique_ptr<GameObject>> m_Objects{};

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
