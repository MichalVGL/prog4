#include "ObjectFinder.h"

#include "Scene.h"
#include "ServiceLocator.h"

std::vector<dae::GameObjectHandle> dae::FindObjects(std::vector<dae::GobjID> objectIds)
{
	std::vector<dae::GameObjectHandle> foundObjects{};
	auto* scene = ServiceLocator::GetSceneSystem().GetCurrentScene();
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