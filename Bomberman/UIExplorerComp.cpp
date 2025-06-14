#include "UIExplorerComp.h"
#include <ObjectFinder.h>

#include <algorithm>
#include <string>
#include <format>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <SDL.h>

#include "BMGameDefines.h"

bm::UIExplorerComp::UIExplorerComp(dae::GameObject& parent, ExplorerMode mode)
	:Component(parent)
{
	auto& inputMngr = dae::InputManager::GetInstance();

	std::unique_ptr<dae::KeyboardBinding> keyBinding{};
	std::unique_ptr<dae::GamepadBinding> padBinding{};

	//switch selected element input
	switch (mode)
	{
	case bm::UIExplorerComp::ExplorerMode::horizontal:

		//keyboard
		keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_RIGHT, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_KeyboardBindings.emplace_back(std::move(keyBinding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_LEFT, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_KeyboardBindings.emplace_back(std::move(keyBinding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		//gamepad
		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, 0, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, 1, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, 0, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, 1, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		break;
	case bm::UIExplorerComp::ExplorerMode::vertical:

		//keyboard
		keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_UP, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_KeyboardBindings.emplace_back(std::move(keyBinding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_DOWN, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_KeyboardBindings.emplace_back(std::move(keyBinding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		//gamepad
		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, 0, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, 1, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { IncementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, 0, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, 1, dae::KeyState::down,
			std::make_unique<dae::FuncCommand>([this]() { DecrementElement(); })));
		m_GamepadBindings.emplace_back(std::move(padBinding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		break;
	}

	//interact input=====================================================================================================

	//keyboard
	keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_X, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { PrimaryInteract(); })));
	m_KeyboardBindings.emplace_back(std::move(keyBinding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	keyBinding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_Z, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { SecondaryInteract(); })));
	m_KeyboardBindings.emplace_back(std::move(keyBinding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	//gamepad
	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_A, 0, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { PrimaryInteract(); })));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_A, 1, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { PrimaryInteract(); })));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_B, 0, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { SecondaryInteract(); })));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_B, 1, dae::KeyState::down,
		std::make_unique<dae::FuncCommand>([this]() { SecondaryInteract(); })));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());
}

bm::UIExplorerComp::~UIExplorerComp()
{
	auto& inputMngr = dae::InputManager::GetInstance();

	for (auto& keyboardBinding : m_KeyboardBindings)
	{
		inputMngr.UnRegisterBinding(keyboardBinding.get());
	}

	for (auto& gamepadBinding : m_GamepadBindings)
	{
		inputMngr.UnRegisterBinding(gamepadBinding.get());
	}
}

void bm::UIExplorerComp::Start()
{
	auto uiObjects = dae::FindObjects({ IUI_GOBJID });
	if (uiObjects.size() == 0)
	{
		std::cout << std::format("Warning: no interactable UI elements found [UIExplorerComp]\n");
	}

	for (const auto& obj : uiObjects)
	{
		auto* uiComp = obj->GetComponent<bm::UIComp>();
		if (uiComp)
		{
			m_UIElements.emplace_back(obj, uiComp);
		}
		else
		{
			std::cout << std::format("Warning: interactable UI element '{}' has no UIComp [UIExplorerComp]\n", obj->GetName());
		}
	}

	if (m_UIElements.empty() == false)
	{
		m_UIElements.at(m_SelectedIndex).second->Select();	//select the first element
	}
}

void bm::UIExplorerComp::IncementElement()
{
	ValidateHandles();

	if (m_UIElements.empty())
		return;

	m_UIElements.at(m_SelectedIndex).second->UnSelect();
	m_SelectedIndex++;
	if (m_SelectedIndex >= static_cast<int>(m_UIElements.size()))
	{
		m_SelectedIndex = 0;
	}
	m_UIElements.at(m_SelectedIndex).second->Select();
}

void bm::UIExplorerComp::DecrementElement()
{
	ValidateHandles();

	if (m_UIElements.empty())
		return;

	m_UIElements.at(m_SelectedIndex).second->UnSelect();
	m_SelectedIndex--;
	if (m_SelectedIndex < 0)
	{
		m_SelectedIndex = static_cast<int>(m_UIElements.size()) - 1;
	}
	m_UIElements.at(m_SelectedIndex).second->Select();
}

void bm::UIExplorerComp::PrimaryInteract()
{
	if (ValidateHandles() == false)
	{
		return; //handles changed
	}
	m_UIElements.at(m_SelectedIndex).second->PrimaryInteract();
}

void bm::UIExplorerComp::SecondaryInteract()
{
	if (ValidateHandles() == false)
	{
		return; //handles changed
	}
	m_UIElements.at(m_SelectedIndex).second->SecondaryInteract();
}

bool bm::UIExplorerComp::ValidateHandles()
{
	auto loc = std::remove_if(m_UIElements.begin(), m_UIElements.end(),
		[](const std::pair<dae::GameObjectHandle, bm::UIComp*>& pair)
		{
			return pair.first.Get() == nullptr;
		});

	if (loc != m_UIElements.end())
	{
		m_UIElements.erase(loc, m_UIElements.end());

		if (m_UIElements.empty())
		{
			std::cout << std::format("Warning: no more interactable UI elements found, all are deleted [UIExplorerComp]\n");
		}
		return false;
	}

	return true;
}
