#ifndef BOMBDEPLOYERCOMP_H
#define BOMBDEPLOYERCOMP_H

#include "Component.h"

#include <Command.h>

namespace bm
{
	class BombDeployerComp final : public dae::Component	//Args: 
	{
	public:
		BombDeployerComp(dae::GameObject& parent);

		BombDeployerComp(const BombDeployerComp& other) = default;
		BombDeployerComp(BombDeployerComp&& other) noexcept = default;
		BombDeployerComp& operator=(const BombDeployerComp& other) = default;
		BombDeployerComp& operator=(BombDeployerComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

		void DeployBomb();		//deploy a bomb if possible
		void DetonateLastBomb();	

	private:

		void ValidateBombHandles();	//update the bomb handles (remove if nullptr == bomb deleted)

		std::vector<dae::GameObjectHandle> m_Bombs{};	//deployed bombs

	};

	class DeployCommand final : public dae::Command
	{
	public:
		DeployCommand(dae::GameObject& gObj);	//make sure to add BombDeployerComp to the GameObject before creating this command
		// Inherited via Command
		void Execute() override;
	private:
		dae::ReqComp<bm::BombDeployerComp> m_BombDeployerComp{};
	};

	class DetonateCommand final : public dae::Command
	{
	public:
		DetonateCommand(dae::GameObject& gObj);	//make sure to add BombDeployerComp to the GameObject before creating this command
		// Inherited via Command
		void Execute() override;
	private:
		dae::ReqComp<bm::BombDeployerComp> m_BombDeployerComp{};
	};
}
#endif // !BOMBDEPLOYERCOMP_H