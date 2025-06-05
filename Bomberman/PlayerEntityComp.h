#ifndef PLAYERENTITYCOMP_H
#define PLAYERENTITYCOMP_H

#include <Texture.h>
#include <vector>
#include <InputManager.h>
#include <Command.h>

#include "BaseEntityComp.h"
#include "EntityController.h"

//todo, delete entire file

/*
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

		//std::vector<std::unique_ptr<dae::KeyboardBinding>> m_KeyboardBindings{};
		//std::vector<std::unique_ptr<dae::GamepadBinding>> m_GamepadBindings{};

	};


}
*/
#endif // !PLAYERENTITYCOMP_H