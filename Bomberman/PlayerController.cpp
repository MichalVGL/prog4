#include "PlayerController.h"

#define WIN32_LEAN_AND_MEAN
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

#include <glm.hpp>

bm::PlayerController::PlayerController(GameMode mode, bool player2)
{
	if (player2 == false)
	{
		SetupKeyboardInput();
		SetupGamepadInput(1);
		if (mode == GameMode::singleplayer)
		{
			SetupGamepadInput(0);
		}
	}
	else
	{
		SetupGamepadInput(0);
	}
}

bm::PlayerController::~PlayerController()
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

void bm::PlayerController::SetupKeyboardInput()
{
	auto& inputMngr = dae::InputManager::GetInstance();

	//presses
	auto binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_UP, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 1))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_DOWN, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, -1))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_LEFT, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(-1, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_RIGHT, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(1, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	//releases
	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_UP, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_DOWN, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_LEFT, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_RIGHT, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_X, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action1)));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_Z, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action2)));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());


}

void bm::PlayerController::SetupGamepadInput(int gamepadId)
{
	auto& inputMngr = dae::InputManager::GetInstance();

	std::unique_ptr<dae::GamepadBinding> padBinding{};


	//movement==========================================================================
	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, gamepadId, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 1))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, gamepadId, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, -1))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, gamepadId, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(1, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, gamepadId, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(-1, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, gamepadId, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, gamepadId, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, gamepadId, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, gamepadId, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());


	//actions=========================================================================
	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_A, gamepadId, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action1)));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());

	padBinding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_B, gamepadId, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action2)));
	m_GamepadBindings.emplace_back(std::move(padBinding));
	inputMngr.RegisterBinding(m_GamepadBindings.back().get());
}
