#ifndef GAMEACTORCOMMANDS_H
#define GAMEACTORCOMMANDS_H

#include "Command.h"
#include <glm.hpp>

class GameActorComp;

class GameActorCommand : public Command
{
public:
	GameActorCommand(GameActorComp* gameActorComp);
	virtual ~GameActorCommand() = default;
protected:
	GameActorComp* GetGameActor() const;
private:
	GameActorComp* m_pGameActorComp;
};

//==============================================================================

class DirectionCommand final : public GameActorCommand
{
public:
	DirectionCommand(GameActorComp* gameActorComp, const glm::vec2& direction);

	void Execute() override;

private:
	glm::vec2 m_Direction;
};

#endif // !GAMEACTORCOMMANDS_H