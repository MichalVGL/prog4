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

		//const and copy version. Given state should be able to access and modify the input (Action 1 and 2), this shouldn't be used for the state
		//EntityInput GetInput() const
		//{
		//	return m_Input;
		//}

	protected:

		EntityInput m_EntityInput{};

	};
}

#endif // !ENTITYCONTROLLER_H

