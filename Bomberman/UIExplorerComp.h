#ifndef UIEXPLORERCOMP_H
#define UIEXPLORERCOMP_H

#include "Component.h"

#include <vector>
#include <Command.h>
#include <tuple>

#include <InputManager.h>

#include "UIComp.h"

namespace bm
{
	class UIExplorerComp final : public dae::Component	//Args: 
	{
	public:

		enum class ExplorerMode
		{
			horizontal,
			vertical
		};

		UIExplorerComp(dae::GameObject& parent, ExplorerMode mode);

		~UIExplorerComp() override;

		UIExplorerComp(const UIExplorerComp& other) = delete;
		UIExplorerComp(UIExplorerComp&& other) noexcept = delete;
		UIExplorerComp& operator=(const UIExplorerComp& other) = delete;
		UIExplorerComp& operator=(UIExplorerComp&& other) noexcept = delete;

		// -------------------------
		// Base Functions
		// -------------------------  
		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//void OnDestroy() override;
		//--------------------------

		void IncementElement();
		void DecrementElement();

		void PrimaryInteract();
		void SecondaryInteract();

	private:

		bool ValidateHandles();	//return true if unchanged

		std::vector<std::pair<dae::GameObjectHandle, bm::UIComp*>> m_UIElements{};
		int m_SelectedIndex{ 0 };

		std::vector<std::unique_ptr<dae::KeyboardBinding>> m_KeyboardBindings{};
		std::vector<std::unique_ptr<dae::GamepadBinding>> m_GamepadBindings{};
	};

	//class NextElementCommand final : public dae::Command
	//{
	//public:
	//
	//	NextElementCommand(UIExplorerComp& explorerComp)
	//		: m_ExplorerComp(explorerComp)
	//	{
	//	}
	//
	//	// Inherited via Command
	//	void Execute() override
	//	{
	//		m_ExplorerComp.IncementElement();
	//	}
	//
	//private:
	//
	//	UIExplorerComp& m_ExplorerComp;
	//};
}
#endif // !UIEXPLORERCOMP_H