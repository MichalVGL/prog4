#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <memory>

#include "Singleton.h"
#include "Gamepad.h"
#include "Command.h"

namespace dae
{

	using Key = uint16_t;
	using GamepadButton = uint16_t;

	enum class KeyState
	{
		down,
		up,
		pressed
	};

	struct KeyboardBinding
	{
		Key Key;
		KeyState KeyState;
		std::unique_ptr<Command> Command;
	};

	struct GamepadBinding
	{
		GamepadButton GamepadButton;
		int GamepadID;
		KeyState KeyState;
		std::unique_ptr<Command> Command;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager();	//todo, change constructors so you cant create instances outside (singleton class upcoming)

		bool ProcessInput();

		KeyboardBinding CreateBinding(Key key, KeyState keyState, std::unique_ptr<Command>&& command);
		GamepadBinding CreateBinding(GamepadButton gamepadButton, int gamepadID, KeyState keyState, std::unique_ptr<Command>&& command);

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
#endif // !INPUTMANAGER_H
