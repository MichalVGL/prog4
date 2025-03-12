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

DirectionCommand::DirectionCommand(GameActorComp* gameActorComp, const glm::vec2& direction)
	:GameActorCommand(gameActorComp)
	, m_Direction{direction}
{
}

void DirectionCommand::Execute()
{
	GetGameActor()->AddDirection(m_Direction);
}
