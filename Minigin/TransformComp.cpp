//---------------------------
// Include Files
//---------------------------
#include "TransformComp.h"
#include "GameObject.h"

//---------------------------
// Constructor & Destructor
//---------------------------
TransformComp::TransformComp(dae::GameObject& parent)
	: Component{ parent }
	, m_Position{}
{
	// nothing to create
}

const glm::vec2& TransformComp::GetLocalPosition() const
{
	return m_Position;
}

void TransformComp::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
}

void TransformComp::SetLocalPosition(const glm::vec2& newPos)
{
	m_Position = newPos;

	GetOwner().InvalidateWorldPos();
}




