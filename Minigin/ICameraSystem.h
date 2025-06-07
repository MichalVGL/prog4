#ifndef ICAMERASYSTEM_H
#define ICAMERASYSTEM_H

#include "GameObject.h"
#include "Utils.h"
#include <glm.hpp>

namespace dae
{
	class ICameraSystem
	{
	public:

		virtual ~ICameraSystem() = default;

		virtual void AddGObjSubject(GameObjectHandle object) = 0;
		virtual void RemoveGObjSubject(GameObjectHandle object) = 0;

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void SetBounds(Rect bounds) = 0;
		virtual glm::vec2 GetCameraPos() const = 0;
		virtual void SetCameraSpeed(float pixelsPerSecond) = 0;
		virtual void SetCameraDeadZone(float size) = 0;
		virtual void Reset() = 0;
	};
}

#endif // !ICAMERASYSTEM_H
