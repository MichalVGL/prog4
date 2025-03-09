#include "GameActorCommands.h"
#include "GameActorComp.h"

///=========================
/// Base Class
///=========================

GameActorCommand::GameActorCommand(GameActorComp* gameActorComp)
	:m_pGameActorComp{gameActorComp}
{
}

GameActorComp* GameActorCommand::GetGameActor() const
{
	return m_pGameActorComp;
}



///=========================
/// Implementations
///=========================

MoveUpCommand::MoveUpCommand(GameActorComp* gameActorComp)
	:GameActorCommand(gameActorComp)
{
}

void MoveUpCommand::Execute()
{
	GetGameActor()->MoveUp();
}

MoveDownCommand::MoveDownCommand(GameActorComp* gameActorComp)
	:GameActorCommand(gameActorComp)
{
}

void MoveDownCommand::Execute()
{
	GetGameActor()->MoveDown();
}

MoveLeftCommand::MoveLeftCommand(GameActorComp* gameActorComp)
	:GameActorCommand(gameActorComp)
{
}

void MoveLeftCommand::Execute()
{
	GetGameActor()->MoveLeft();
}

MoveRightCommand::MoveRightCommand(GameActorComp* gameActorComp)
	:GameActorCommand(gameActorComp)
{
}

void MoveRightCommand::Execute()
{
	GetGameActor()->MoveRight();
}
