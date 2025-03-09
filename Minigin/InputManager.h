#pragma once
#include <vector>
#include <memory>

#include "Singleton.h"
#include "Gamepad.h"
#include "Command.h"

namespace dae
{

	enum class KeyState
	{
		down,
		up,
		pressed
	};

	struct KeyboardBinding
	{
		uint16_t SDLScanCode;
		KeyState KeyState;
		std::unique_ptr<Command> Command;
	};

	struct GamepadBinding
	{
		uint8_t GamepadButton;
		int GamepadID;
		KeyState KeyState;
		std::unique_ptr<Command> Command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager();	//todo, change constructors so you cant create instances outside (singleton class upcoming)

		bool ProcessInput();

		//template<typename command>
		KeyboardBinding CreateBinding(uint16_t SDLScanCode, KeyState keyState, std::unique_ptr<Command>&& command);
		GamepadBinding CreateBinding(uint8_t gamepadButton, int gamepadID, KeyState keyState, std::unique_ptr<Command>&& command);

		void RegisterBinding(KeyboardBinding* keyboardBinding);
		void RegisterBinding(GamepadBinding* gamepadBinding);

		void UnRegisterBinding(KeyboardBinding* keyboardBinding);
		void UnRegisterBinding(GamepadBinding* gamepadBinding);

	private:

		static constexpr int MAX_GAMEPADS{ 4 };
		std::vector<Gamepad> m_Gamepads;

		std::vector<KeyboardBinding*> m_KeyboadBindings;
		std::vector<GamepadBinding*> m_GamepadBindings;

	};

}
