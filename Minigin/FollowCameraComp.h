#ifndef FOLLOWCAMERACOMP_H
#define FOLLOWCAMERACOMP_H

#include "Component.h"
#include "TransformComp.h"

//this component will follow the render offset set by the camerasystem (usefull for UI)

namespace dae
{
	class FollowCameraComp final : public dae::Component	//Args: 
	{
	public:
		FollowCameraComp(dae::GameObject& parent);

		FollowCameraComp(const FollowCameraComp& other) = default;
		FollowCameraComp(FollowCameraComp&& other) noexcept = default;
		FollowCameraComp& operator=(const FollowCameraComp& other) = default;
		FollowCameraComp& operator=(FollowCameraComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------



	private:

		ReqComp<TransformComp> m_TransformComp{};

	};
}
#endif // !FOLLOWCAMERACOMP_H