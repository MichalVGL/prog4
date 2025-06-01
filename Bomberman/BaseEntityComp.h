#ifndef BASEENTITYCOMP_H
#define BASEENTITYCOMP_H

#include "Component.h"

namespace bm
{
	class BaseEntityComp final : public dae::Component	//Args: 
	{
	public:
		BaseEntityComp(dae::GameObject& parent);

		BaseEntityComp(const BaseEntityComp& other) = default;
		BaseEntityComp(BaseEntityComp&& other) noexcept = default;
		BaseEntityComp& operator=(const BaseEntityComp& other) = default;
		BaseEntityComp& operator=(BaseEntityComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------


		virtual void Kill() = 0;


	private:



	};
}
#endif // !BASEENTITYCOMP_H