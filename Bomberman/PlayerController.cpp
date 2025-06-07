#include "PlayerController.h"

#define WIN32_LEAN_AND_MEAN
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

#include <glm.hpp>

bm::PlayerController::PlayerController()
{
	SetupInput();
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

void bm::PlayerController::SetupInput()
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

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_X, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action1)));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_Z, dae::KeyState::down,
		std::make_unique<ActionCommand>(m_EntityInput.action2)));
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


}
