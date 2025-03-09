#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <glm.hpp>
#include <vector>
#include "Component.h"
#include "InputManager.h"


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------

//TODO change name without comp for all components
class GameActorComp final : public Component	//Args: float:moveSpeed, bool:useController
{
public:
	GameActorComp(dae::GameObject& parent, float moveSpeed, bool useController);	
	~GameActorComp();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	GameActorComp(const GameActorComp& other)						= default;
	GameActorComp(GameActorComp&& other) noexcept					= default;
	GameActorComp& operator=(const GameActorComp& other)			= default;
	GameActorComp& operator=(GameActorComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private: 

	std::vector<std::unique_ptr<dae::KeyboardBinding>> m_KeyboardBindings;
	std::vector<std::unique_ptr<dae::GamepadBinding>> m_GamepadBindings;

	glm::vec2 m_Direction;
	float m_MoveSpeed;

};

 
