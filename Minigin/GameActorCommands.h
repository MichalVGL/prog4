#pragma once
#include "Command.h"

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

class MoveUpCommand final : public GameActorCommand
{
public:
	MoveUpCommand(GameActorComp* gameActorComp);

	void Execute() override;
};

class MoveDownCommand final : public GameActorCommand
{
public:
	MoveDownCommand(GameActorComp* gameActorComp);

	void Execute() override;
};

class MoveLeftCommand final : public GameActorCommand
{
public:
	MoveLeftCommand(GameActorComp* gameActorComp);

	void Execute() override;
};

class MoveRightCommand final : public GameActorCommand
{
public:
	MoveRightCommand(GameActorComp* gameActorComp);

	void Execute() override;
};

