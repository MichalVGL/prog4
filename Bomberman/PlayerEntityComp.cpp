#include "PlayerEntityComp.h"

#define WIN32_LEAN_AND_MEAN
#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>


#include "BMGameDefines.h"

bm::PlayerEntityComp::PlayerEntityComp(dae::GameObject& parent, const EntityStats& entityStats)
	:BaseEntityComp(parent, entityStats)
{
	SetupInput();

	//setup the sprite
	m_SpriteComp->LoadTexture(s_PlayerTextureEntry);
	m_SpriteComp->AddSpriteEntry(dae::SpriteEntry("MoveDown", { 0, TILE_SIZE * 3, TILE_SIZE * 4, TILE_SIZE }, 4, 1));
	m_SpriteComp->AddSpriteEntry(dae::SpriteEntry("MoveUp", { 0, TILE_SIZE * 2, TILE_SIZE * 4, TILE_SIZE }, 4, 1));
	m_SpriteComp->AddSpriteEntry(dae::SpriteEntry("MoveRight", { 0, TILE_SIZE * 1, TILE_SIZE * 4, TILE_SIZE }, 4, 1));
	m_SpriteComp->AddSpriteEntry(dae::SpriteEntry("Death", { 0, 0, TILE_SIZE * 7, TILE_SIZE }, 7, 1));
}

bm::PlayerEntityComp::~PlayerEntityComp()
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

void bm::PlayerEntityComp::Update(float deltaTime)
{
	UpdateState(deltaTime);
}

//HELPERS===============================================

void bm::PlayerEntityComp::SetupInput()
{
	auto& inputMngr = dae::InputManager::GetInstance();

	//presses
	auto binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_W, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 1))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_S, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, -1))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_A, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(-1, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_D, dae::KeyState::pressed,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(1, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	//releases
	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_W, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_S, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_A, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());

	binding = std::make_unique<dae::KeyboardBinding>(inputMngr.CreateBinding(SDL_SCANCODE_D, dae::KeyState::up,
		std::make_unique<DirectionCommand>(m_EntityInput, glm::ivec2(0, 0))));
	m_KeyboardBindings.emplace_back(std::move(binding));
	inputMngr.RegisterBinding(m_KeyboardBindings.back().get());
}
