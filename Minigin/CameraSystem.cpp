#include "CameraSystem.h"

#include <algorithm>
#include <numeric>
#include <iostream>

#include "ServiceLocator.h"
#include "Utils.h"

void dae::CameraSystem::AddGObjSubject(GameObjectHandle object)
{
	if (object.Get() == nullptr)
		return; // no object to add
	if (std::find_if(m_Subjects.begin(), m_Subjects.end(), [&](GameObjectHandle& handle) { return handle.Get() == object.Get(); })
		== m_Subjects.end())
	{
		m_Subjects.push_back(object);
	}
}

void dae::CameraSystem::RemoveGObjSubject(GameObjectHandle object)
{
	m_Subjects.erase(std::remove_if(m_Subjects.begin(), m_Subjects.end(),
		[&](GameObjectHandle& handle) { return handle.Get() == object.Get(); })
		, m_Subjects.end());
}

void dae::CameraSystem::Start()
{
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	m_CameraPosition = renderSystem.GetCanvasSize() / 2.f;
}

void dae::CameraSystem::Update(float deltaTime)
{
	ValidateSubjects();
	
	if (m_Subjects.empty())
		return; // no subjects to follow
	
	glm::vec2 addedPos = std::accumulate(m_Subjects.begin(), m_Subjects.end(), glm::vec2(0, 0),
		[](const glm::vec2& acc, const GameObjectHandle& handle) {
			return acc + handle->GetWorldPos();
		});
	
	m_TargetPosition = addedPos / static_cast<float>(m_Subjects.size());

	ValidateTarget();

	glm::vec2 toTarget = m_TargetPosition - m_CameraPosition;
	float distanceSq = dae::LengthSquared(toTarget);
	if (distanceSq < m_SnapDistance * m_SnapDistance)
		m_CameraPosition = m_TargetPosition;	// snap to target if within snap distance
	else										// or use a smooth transition
	{
		m_CameraPosition += m_CameraSpeedFactor * toTarget * deltaTime;
	}

	ValidateTarget();

	//update the renderoffset
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	glm::ivec2 offset = static_cast<glm::ivec2>(m_CameraPosition - renderSystem.GetCanvasSize() / 2.f);
	renderSystem.SetRenderOffset(static_cast<glm::ivec2>(offset));
}

glm::vec2 dae::CameraSystem::GetCameraPos() const
{
	return m_CameraPosition;
}

void dae::CameraSystem::SetCameraSpeedFactor(float speedFactor)
{
	if (speedFactor > 0)
		m_CameraSpeedFactor = speedFactor;
}

void dae::CameraSystem::SetBounds(Rect bounds)
{
	m_Bounds = bounds;
}

void dae::CameraSystem::Reset()
{
	m_Bounds = Rect{ 0, 0, 0, 0 };
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	m_CameraPosition = renderSystem.GetCanvasSize() / 2.f;
	m_TargetPosition = m_CameraPosition;
	m_Subjects.clear();
}

void dae::CameraSystem::ValidateSubjects()
{
	m_Subjects.erase(std::remove_if(m_Subjects.begin(), m_Subjects.end(),
		[](GameObjectHandle& handle) { return handle.Get() == nullptr; }),
		m_Subjects.end());
}

void dae::CameraSystem::ValidateTarget()
{
	auto window = dae::ServiceLocator::GetRenderSystem().GetCanvasSize();
	if (m_Bounds.w < window.x - 0.1f || m_Bounds.h < window.y - 0.1f)
	{
		return;	//invalid bounds
	}
	m_TargetPosition.x = std::clamp(m_TargetPosition.x, static_cast<float>(m_Bounds.x) + window.x / 2.f, static_cast<float>(m_Bounds.x + m_Bounds.w) - window.x / 2.f);
	m_TargetPosition.y = std::clamp(m_TargetPosition.y, static_cast<float>(m_Bounds.y) + window.y / 2.f, static_cast<float>(m_Bounds.y + m_Bounds.h) - window.y / 2.f);
}
