//---------------------------
// Include Files
//---------------------------
#include "TransformComp.h"
#include "GameObject.h"


dae::TransformComp::TransformComp(dae::GameObject& parent)
	: Component{ parent }
	, m_Position{}
{
}

const glm::vec2& dae::TransformComp::GetLocalPosition() const
{
	return m_Position;
}

void dae::TransformComp::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec2(x, y));
}

void dae::TransformComp::SetLocalPosition(const glm::vec2& newPos)
{
	m_Position = newPos;

	GetOwner().InvalidateWorldPos();
}




