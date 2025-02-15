//---------------------------
// Include Files
//---------------------------
#include "TransformComp.h"

//---------------------------
// Constructor & Destructor
//---------------------------
TransformComp::TransformComp(dae::GameObject& parent)
	: Component{ parent }
	, m_Position{}
{
	// nothing to create
}

TransformComp::~TransformComp()
{
	// nothing to destroy
}

const glm::vec2& TransformComp::GetPosition() const
{
	return m_Position;
}

void TransformComp::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}




