#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <InputManager.h>
#include <Command.h>
#include <memory>

#include "EntityController.h"
#include "LevelUtils.h"

namespace bm
{
	class PlayerController final : public EntityController
	{
	public:

		PlayerController(GameMode mode, bool player2 = false); 

		~PlayerController() override;

		PlayerController(const PlayerController& other) = default;
		PlayerController(PlayerController&& other) noexcept = default;
		PlayerController& operator=(const PlayerController& other) = default;
		PlayerController& operator=(PlayerController&& other) noexcept = default;

		void Update(EntityCondition) override {};	//update doesnt do anything with the playercontroller, input is handled by commands

	private:

		void SetupKeyboardInput();
		void SetupGamepadInput(int gamepadId);	

		std::vector<std::unique_ptr<dae::KeyboardBinding>> m_KeyboardBindings{};
		std::vector<std::unique_ptr<dae::GamepadBinding>> m_GamepadBindings{};

	};

	class DirectionCommand final : public dae::Command
	{
	public:
		DirectionCommand(EntityInput& input, const glm::ivec2& direction)
			:m_Direction{ direction }
			, m_Input{ input }
		{
		}

		void Execute() override
		{
			m_Input.direction = m_Direction;
		}

	private:

		glm::ivec2 m_Direction;
		EntityInput& m_Input;
	};

	class ActionCommand final : public dae::Command
	{
	public:
		ActionCommand(bool& boolInput)
			: m_Input{ boolInput }
		{
		}

		void Execute() override
		{
			m_Input = true;
		}

	private:
		bool& m_Input;
	};
}

#endif // !PLAYERCONTROLLER_H

