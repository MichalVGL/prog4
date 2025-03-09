//---------------------------
// Include Files
//---------------------------
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>
#include "GameActorComp.h"
#include "GameActorCommands.h"
#include "Time.h"

GameActorComp::GameActorComp(dae::GameObject& parent, float moveSpeed, bool useController)
	:Component(parent)
	, m_KeyboardBindings{}
	, m_GamepadBindings{}
	, m_Direction{ 0.f, 0.f }
	, m_MoveSpeed{ moveSpeed }
{
	if (useController)
	{
		auto& inputMngr = dae::InputManager::GetInstance();
		auto binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, 0, dae::KeyState::pressed, std::make_unique<MoveUpCommand>(this)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, 0, dae::KeyState::pressed, std::make_unique<MoveDownCommand>(this)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, 0, dae::KeyState::pressed, std::make_unique<MoveLeftCommand>(this)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, 0, dae::KeyState::pressed, std::make_unique<MoveRightCommand>(this)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());
	}
	else
	{
		auto& inputMngr = dae::InputManager::GetInstance();

		auto binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_W, dae::KeyState::pressed, std::make_unique<MoveUpCommand>(this)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_S, dae::KeyState::pressed, std::make_unique<MoveDownCommand>(this)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_A, dae::KeyState::pressed, std::make_unique<MoveLeftCommand>(this)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_D, dae::KeyState::pressed, std::make_unique<MoveRightCommand>(this)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());
	}
}

GameActorComp::~GameActorComp()
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

void GameActorComp::Update(float deltaTime)
{
	if (std::abs(m_Direction.x) + std::abs(m_Direction.y) > 0.1f)
	{
		auto dir = glm::normalize(m_Direction);
		
		auto& pos =  GetOwner().GetLocalPosition();
		GetOwner().SetLocalPosition(pos + (dir * m_MoveSpeed * deltaTime));
		
		m_Direction = { 0.f, 0.f };	//reset
	}
}

void GameActorComp::MoveUp()
{
	m_Direction.y = -1.f;
}

void GameActorComp::MoveDown()
{
	m_Direction.y = 1.f;
}

void GameActorComp::MoveLeft()
{
	m_Direction.x = -1.f;
}

void GameActorComp::MoveRight()
{
	m_Direction.x = 1.f;
}




