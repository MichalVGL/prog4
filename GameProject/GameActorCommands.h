#ifndef GAMEACTORCOMMANDS_H
#define GAMEACTORCOMMANDS_H

#include <glm.hpp>
#include <GameObject.h>
#include <Component.h>

#include "Command.h"

class GameActorComp;

class GameActorCommand : public dae::Command
{
public:
	GameActorCommand(GameActorComp* pGameActor);
	virtual ~GameActorCommand() = default;
protected:
	dae::ReqComp<GameActorComp> m_GameActorComp{};
	dae::GameObject& m_GameObject;
};

//==============================================================================

class DirectionCommand final : public GameActorCommand
{
public:
	DirectionCommand(GameActorComp* pGameActor, const glm::vec2& direction);

	void Execute() override;

private:
	glm::vec2 m_Direction;
};

//===============
class DamageCommand final : public GameActorCommand
{
public:
	DamageCommand(GameActorComp* pGameActor);

	void Execute() override;
};

//===============
class AddScoreCommand final : public GameActorCommand
{
public:
	AddScoreCommand(GameActorComp* pGameActor, int amount);

	void Execute() override;

private:
	int m_Amount;
};

#endif // !GAMEACTORCOMMANDS_H