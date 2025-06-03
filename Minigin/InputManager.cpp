#include <SDL.h>
//#include <Windows.h>
//#include <Xinput.h>
#include <algorithm>

#include "InputManager.h"
#include "Keyboard.h"
#include "imgui_impl_sdl2.h"

dae::InputManager::InputManager()
	:m_Gamepads{}
	, m_KeyboadBindings{}
	, m_GamepadBindings{}
{
	m_Gamepads.reserve(MAX_GAMEPADS);
	for (int id{ 0 }; id < MAX_GAMEPADS; ++id)
	{
		m_Gamepads.emplace_back(id);
	}
}

bool dae::InputManager::ProcessInput()
{
	//Event based Input
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;	
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	//Update input data====================================
	//Update Keyboard
	Keyboard::GetInstance().UpdateInput();

	//Update Gamepads
	for (auto& gamePad : m_Gamepads)
	{
		gamePad.UpdateInput();
	}

	//check bindings=======================================
	//Update keyboard bindings
	for (auto& keyboardBind : m_KeyboadBindings)
	{
		switch (keyboardBind->KeyState)
		{
		case KeyState::down:
			if (Keyboard::GetInstance().IsButtonDown(keyboardBind->Key))
				keyboardBind->Command->Execute();
			break;
		case KeyState::up:
			if (Keyboard::GetInstance().IsButtonUp(keyboardBind->Key))
				keyboardBind->Command->Execute();
			break;
		case KeyState::pressed:
			if (Keyboard::GetInstance().IsButtonPressed(keyboardBind->Key))
				keyboardBind->Command->Execute();
			break;
		}
	}

	//Update gamepad bindings
	for (auto& gamepadBind : m_GamepadBindings)
	{
		switch (gamepadBind->KeyState)
		{
		case KeyState::down:
			if (m_Gamepads[gamepadBind->GamepadID].IsButtonDown(gamepadBind->GamepadButton))
				gamepadBind->Command->Execute();
			break;
		case KeyState::up:
			if (m_Gamepads[gamepadBind->GamepadID].IsButtonUp(gamepadBind->GamepadButton))
				gamepadBind->Command->Execute();
			break;
		case KeyState::pressed:
			if (m_Gamepads[gamepadBind->GamepadID].IsButtonPressed(gamepadBind->GamepadButton))
				gamepadBind->Command->Execute();
			break;
		}
	}

	return true;	//continue game
}

dae::KeyboardBinding dae::InputManager::CreateBinding(Key key, KeyState keyState, std::unique_ptr<Command>&& command)	//change command to not use unique pointer here
{
	assert(key < SDL_NUM_SCANCODES && "Invalid SDLScancode given to keyboard binding");
	assert(command && "Command cannot be null when adding a binding");

	KeyboardBinding binding{};
	binding.Key = key;
	binding.KeyState = keyState;
	binding.Command = std::move(command);

	return binding;
}

dae::GamepadBinding dae::InputManager::CreateBinding(GamepadButton gamepadButton, int gamepadID, KeyState keyState, std::unique_ptr<Command>&& command)
{
	assert(Gamepad::IsValidGamepadButton(gamepadButton) && "Invalid gamepadButton given to gamepad binding");
	assert(command && "Command cannot be nullptr when adding a binding");

	GamepadBinding binding{};
	binding.GamepadButton = gamepadButton;
	binding.GamepadID = gamepadID;
	binding.KeyState = keyState;
	binding.Command = std::move(command);

	return binding;
}

void dae::InputManager::RegisterBinding(KeyboardBinding* keyboardBinding)
{
	m_KeyboadBindings.emplace_back(keyboardBinding);
}

void dae::InputManager::RegisterBinding(GamepadBinding* gamepadBinding)
{
	m_GamepadBindings.emplace_back(gamepadBinding);
}

void dae::InputManager::UnRegisterBinding(KeyboardBinding* keyboardBinding)
{
	auto loc = std::find(m_KeyboadBindings.begin(), m_KeyboadBindings.end(), keyboardBinding);
	if (loc != m_KeyboadBindings.end())
		m_KeyboadBindings.erase(loc);
}

void dae::InputManager::UnRegisterBinding(GamepadBinding* gamepadBinding)
{
	auto loc = std::find(m_GamepadBindings.begin(), m_GamepadBindings.end(), gamepadBinding);
	if (loc != m_GamepadBindings.end())
		m_GamepadBindings.erase(loc);
}
