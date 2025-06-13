#ifndef EXECUTINGUICOMP_H
#define EXECUTINGUICOMP_H

#include <Command.h>
#include <memory>

#include "UIComp.h"

namespace bm
{
	class ExecutingUIComp final : public bm::UIComp	//Args: std::unique_ptr<dae::Command>&& command
	{
	public:
		ExecutingUIComp(dae::GameObject& parent, std::unique_ptr<dae::Command>&& command);

		ExecutingUIComp(const ExecutingUIComp& other) = default;
		ExecutingUIComp(ExecutingUIComp&& other) noexcept = default;
		ExecutingUIComp& operator=(const ExecutingUIComp& other) = default;
		ExecutingUIComp& operator=(ExecutingUIComp&& other) noexcept = default;

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

		//inherited
		void PrimaryInteract() override;

	private:

		std::unique_ptr<dae::Command> m_pCommand;	//command to execute

	};
}
#endif // !EXECUTINGUICOMP_H