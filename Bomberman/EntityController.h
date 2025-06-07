#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include "EntityUtils.h"

namespace bm
{
	//Base for the EntityController, which handles input
	class EntityController
	{
	public:

		virtual ~EntityController() = default;
		virtual void Update(EntityCondition condition) = 0;

		EntityInput& GetInputRef()
		{
			return m_EntityInput;
		}

	protected:

		EntityInput m_EntityInput{};

	};
}

#endif // !ENTITYCONTROLLER_H

