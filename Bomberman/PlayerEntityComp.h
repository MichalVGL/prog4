#ifndef PLAYERENTITYCOMP_H
#define PLAYERENTITYCOMP_H

#include <Texture.h>
#include <vector>
#include <InputManager.h>
#include <Command.h>

#include "BaseEntityComp.h"

namespace bm
{
	class PlayerEntityComp final : public BaseEntityComp	//Args: const EntityStats& entityStats
	{
	public:
		PlayerEntityComp(dae::GameObject& parent, const EntityStats& entityStats);

		~PlayerEntityComp() override;
		PlayerEntityComp(const PlayerEntityComp& other) = default;
		PlayerEntityComp(PlayerEntityComp&& other) noexcept = default;
		PlayerEntityComp& operator=(const PlayerEntityComp& other) = default;
		PlayerEntityComp& operator=(PlayerEntityComp&& other) noexcept = default;

		// -------------------------
		// Base Functions
		// -------------------------  
		//void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------



	private:

		void SetupInput();

		static constexpr dae::TextureEntry s_PlayerTextureEntry{"Bomberman.png"};

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

}
#endif // !PLAYERENTITYCOMP_H