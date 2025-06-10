#include "FollowCameraComp.h"

#include "ServiceLocator.h"

dae::FollowCameraComp::FollowCameraComp(dae::GameObject& parent)
	:Component(parent)
{
	m_TransformComp.Init(GetOwner());
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	m_TransformComp->SetLocalPosition(renderSystem.GetCanvasSize()/2.f);
}

void dae::FollowCameraComp::LateUpdate(float)
{
	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();

	m_TransformComp->SetLocalPosition(cameraSystem.GetCameraPos());
}
