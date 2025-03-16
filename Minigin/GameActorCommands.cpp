#include "GameActorCommands.h"
#include "GameActorComp.h"
#include "HealthComp.h"
#include "ScoreComp.h"

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

//=====================
DamageCommand::DamageCommand(GameActorComp* gameActorComp)
	:GameActorCommand(gameActorComp)
{
}

void DamageCommand::Execute()
{
	if (auto* hComp{ GetGameActor()->TryGetOwnerComponent<HealthComp>() }; hComp != nullptr)
	{
		hComp->Damage();
	}
}

//=====================
AddScoreCommand::AddScoreCommand(GameActorComp* gameActorComp, int amount)
	:GameActorCommand(gameActorComp)
	, m_Amount{ amount }
{
}

void AddScoreCommand::Execute()
{
	if (auto* scoreComp{ GetGameActor()->TryGetOwnerComponent<ScoreComp>() }; scoreComp != nullptr)
	{
		scoreComp->AddScore(m_Amount);
	}
}
