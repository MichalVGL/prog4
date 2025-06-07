#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "ICameraSystem.h"

namespace dae
{
	class CameraSystem final : public ICameraSystem
	{
	public:

		void AddGObjSubject(GameObjectHandle object) override;
		void RemoveGObjSubject(GameObjectHandle object) override;

		void Start() override;
		void Update(float deltaTime) override;

		void SetBounds(Rect bounds) override;
		glm::vec2 GetCameraPos() const override;
		void SetCameraSpeed(float pixelsPerSecond) override;
		void SetCameraDeadZone(float size);

		void Reset() override;

	private:

		void ValidateSubjects();	//remove subjects that are no longer valid (deleted)
		void ValidateTarget();	//checks the target compared to the bounds


		std::vector<GameObjectHandle> m_Subjects{};	//objects that the camera will follow
		glm::vec2 m_CameraPosition{}; //camera position, follows the targetpos
		glm::vec2 m_TargetPosition{}; //average of the subjects
		Rect m_Bounds{ 0, 0, 0, 0 };	//camera bounds

		float m_CameraSpeed{ 50.f };	//camera speed, how fast it moves towards the target position
		float m_DeadZone{ 10.f };	//deadzone, how far the camera can be from the target before it starts moving
	};
}

#endif // !CAMERASYSTEM_H
