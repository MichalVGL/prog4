#ifndef OBJECTFINDER_H
#define OBJECTFINDER_H

#include <vector>

#include "GameObject.h"

namespace dae
{
	std::vector<dae::GameObjectHandle> FindObjects(std::vector<dae::GobjID> objectIds);
}

#endif // !OBJECTFINDER_H
