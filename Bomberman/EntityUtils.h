#ifndef ENTITYUTILS_H
#define ENTITYUTILS_H

#include <glm.hpp>

namespace bm
{
	enum class EntityStateType
	{
		Idle,
		Moving,
		Dying
	};

	struct EntityCondition //given to the controller
	{
		bool stateChanged{ true };
		EntityStateType stateType;
		glm::ivec2 position;	//position of the entity, used for pathfinding
	};

	struct EntityStats	//stats the state should take into acccount
	{
		float movementSpeed;
	};

	struct EntityInput	//input the state uses
	{
		glm::ivec2 direction;
		bool action1;
		bool action2;
	};
}

#endif // !ENTITYUTILS_H
