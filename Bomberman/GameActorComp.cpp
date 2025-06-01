//---------------------------
// Include Files
//---------------------------
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

#include <ServiceLocator.h>

#include "GameActorComp.h"
#include "GameActorCommands.h"
#include "Time.h"
#include "HealthComp.h"
#include "ScoreComp.h"

GameActorComp::GameActorComp(dae::GameObject& parent, float moveSpeed, int playerId)
	:Component(parent)
	, m_PlayerID{ playerId }
	, m_Direction{ 0.f, 0.f }
	, m_MoveSpeed{ moveSpeed }
{
	auto& inputMngr = dae::InputManager::GetInstance();

	if (playerId == 0)	//keyboard
	{
		auto binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_W, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(0.f, 1.f))));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_S, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(0.f, -1.f))));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_A, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(-1.f, 0.f))));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_D, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(1.f, 0.f))));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());
	}
	else //gamepad
	{
		auto gamepadID{ playerId - 1 };
		auto binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_UP, gamepadID, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(0.f, 1.f))));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_DOWN, gamepadID, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(0.f, -1.f))));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_LEFT, gamepadID, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(-1.f, 0.f))));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_DPAD_RIGHT, gamepadID, dae::KeyState::pressed,
			std::make_unique<DirectionCommand>(this, glm::vec2(1.f, 0.f))));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());
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

void GameActorComp::Start()
{
	auto& inputMngr = dae::InputManager::GetInstance();

	//add damage/pickup binding
	if (m_PlayerID == 0)	//keyboard
	{
		//damage
		auto binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_C, dae::KeyState::down,
			std::make_unique<DamageCommand>(this)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());


		//pickup
		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_Z, dae::KeyState::down,
			std::make_unique<AddScoreCommand>(this, 100)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

		binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_X, dae::KeyState::down,
			std::make_unique<AddScoreCommand>(this, 100)));
		m_KeyboardBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_KeyboardBindings.back().get());
	}
	else //gamepad
	{
		int padId{ m_PlayerID - 1 };

		//damage
		auto binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_X, padId, dae::KeyState::down,
			std::make_unique<DamageCommand>(this)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());


		//pickup
		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_A, padId, dae::KeyState::down,
			std::make_unique<AddScoreCommand>(this, 50)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());

		binding = std::make_unique<dae::GamepadBinding>(inputMngr.CreateBinding(XINPUT_GAMEPAD_B, padId, dae::KeyState::down,
			std::make_unique<AddScoreCommand>(this, 50)));
		m_GamepadBindings.emplace_back(std::move(binding));
		inputMngr.RegisterBinding(m_GamepadBindings.back().get());
	}
}

void GameActorComp::Update(float deltaTime)
{
	if (std::abs(m_Direction.x) + std::abs(m_Direction.y) > 0.1f)
	{
		auto dir = glm::normalize(m_Direction);

		auto& pos = GetOwner().GetLocalPosition();
		GetOwner().SetLocalPosition(pos + (dir * m_MoveSpeed * deltaTime));

		m_Direction = { 0.f, 0.f };	//reset
	}
}

void GameActorComp::AddDirection(const glm::vec2& direction)
{
	m_Direction += direction;
}




