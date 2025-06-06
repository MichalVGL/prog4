#ifndef OBJECTFINDER_H
#define OBJECTFINDER_H

#include <vector>

#include <Scene.h>
#include <SceneManager.h>

namespace bm
{
	std::vector<dae::GameObjectHandle> FindObjects(std::vector<dae::GobjID> objectIds)
	{
		std::vector<dae::GameObjectHandle> foundObjects{};
		auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
		if (!scene)
			return foundObjects;
		for (const auto& objectId : objectIds)
		{
			auto objects = scene->GetObjectByID(objectId);
			if (!objects.empty())
			{
				foundObjects.insert(foundObjects.end(), objects.begin(), objects.end());
			}
		}
		return foundObjects;
	}
}

#endif // !OBJECTFINDER_H
