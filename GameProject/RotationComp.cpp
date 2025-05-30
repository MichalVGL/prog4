//---------------------------
// Include Files
//---------------------------
#include "RotationComp.h"
#include "TransformComp.h"

RotationComp::RotationComp(dae::GameObject& parent, float degreesPerSecond)
	:Component(parent)
	, m_RadiansPerSecond{}
	, m_IsActive{}
{
	SetRotationSpeed(degreesPerSecond);
}

void RotationComp::Start()
{
	m_TransformComp.Init(GetOwner());
}

void RotationComp::Update(float deltaTime)
{
	if (m_IsActive)
	{
		float cosAngle = std::cos(m_RadiansPerSecond * deltaTime);
		float sinAngle = std::sin(m_RadiansPerSecond * deltaTime);

		const auto& pos = m_TransformComp->GetLocalPosition();

		m_TransformComp->SetLocalPosition(
			pos.x * cosAngle - pos.y * sinAngle,	// [ cos  -sin ]
			pos.x * sinAngle + pos.y * cosAngle);	// [ sin   cos ]
	}
}

void RotationComp::SetRotationSpeed(float degreesPerSecond)
{
	m_RadiansPerSecond = glm::radians(degreesPerSecond);

	if (std::abs(m_RadiansPerSecond) < 0.0001)
		m_IsActive = false;
	else
		m_IsActive = true;
	
}
