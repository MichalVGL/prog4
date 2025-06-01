#include "GameActorCommands.h"
#include "GameActorComp.h"

///=========================
/// Base Class
///=========================

GameActorCommand::GameActorCommand(GameActorComp* pGameActor)
	:m_GameObject{pGameActor->GetOwner()}
{
	m_GameActorComp.Init(pGameActor);
}

///=========================
/// Implementations
///=========================

DirectionCommand::DirectionCommand(GameActorComp* pGameActor, const glm::vec2& direction)
	:GameActorCommand(pGameActor)
	, m_Direction{direction}
{
}

void DirectionCommand::Execute()
{
	m_GameActorComp->AddDirection(m_Direction);
}

//=====================
DamageCommand::DamageCommand(GameActorComp* pGameActor)
	:GameActorCommand(pGameActor)
{
}

void DamageCommand::Execute()
{
	//if (auto* hComp{ m_GameObject.TryGetComponent<HealthComp>() }; hComp != nullptr)
	{
		//hComp->Damage();
	}
}

//=====================
AddScoreCommand::AddScoreCommand(GameActorComp* pGameActor, int amount)
	:GameActorCommand(pGameActor)
	, m_Amount{ amount }
{
}

void AddScoreCommand::Execute()
{
	//if (auto* scoreComp{ m_GameObject.TryGetComponent<ScoreComp>() }; scoreComp != nullptr)
	{
		//scoreComp->AddScore(m_Amount);
	}
}
