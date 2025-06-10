#include "AIController.h"

#include <ServiceLocator.h>

#include "BMServiceLocator.h"
#include "BMGameDefines.h"

bm::AIController::AIController(Intelligence intelligence, dae::GameObject& entity)
{
	// Initialize pRandomPathCommand before using it
	auto pRandomPathCommand = std::make_unique<bm::RandomPathingCommand>(entity, m_Path, RANDOMPATH_MINTILES, RANDOMPATH_MAXTILES);

	// Assign to m_pRandomPathingCommand
	m_pRandomPathingCommand = std::move(pRandomPathCommand);	//setup backup

	// Reinitialize pRandomPathCommand for further use
	pRandomPathCommand = std::make_unique<bm::RandomPathingCommand>(entity, m_Path, RANDOMPATH_MINTILES, RANDOMPATH_MAXTILES);

	switch (intelligence)
	{
	case bm::AIController::Intelligence::low:
		m_pPathingCommand = std::move(pRandomPathCommand);	//low intelligence AI will use random pathing
		break;
	case bm::AIController::Intelligence::normal:
		m_pPathingCommand = std::make_unique<bm::PathToTargetCommand>(entity, m_Path, &GetPlayer, std::move(pRandomPathCommand));	//normal intelligence AI will use pathfinding to the player
		break;
	default:
		std::cout << "Warning: AIController initialized with unknown intelligence type.\n";
		m_pPathingCommand = std::move(pRandomPathCommand);	//low intelligence AI will use random pathing
		break;
	}
}

void bm::AIController::Update(EntityCondition condition)
{
	if (condition.stateChanged)
	{
		if (condition.stateType == EntityStateType::Idle)
		{
			if (m_Path.empty())	//path completed, get new path using primary pathfinder
			{
				SetNewPath();
			}
			else //path not completed, blocked by something. get random path
			{
				SetRandomPath();
			}
		}
		else if (condition.stateType == EntityStateType::Moving)	//1 tile completed, set new next direction if it's available
		{
			if (!m_Path.empty())
			{
				SetNextInput();
			}
			else
			{
				m_EntityInput.direction = glm::ivec2(0, 0);	//no more path, stop moving when completed (idle, will trigger pathing) 
			}
		}
	}
}

void bm::AIController::SetNewPath()
{
	if (m_pPathingCommand)
		m_pPathingCommand->Execute();	//execute the main pathing command to get a new path
	if (m_Path.empty())	//main pathing command didnt return a valid path, try the random one
		SetRandomPath();
	else
		SetNextInput();	
}

void bm::AIController::SetRandomPath()
{
	if (m_pRandomPathingCommand)
		m_pRandomPathingCommand->Execute();

	SetNextInput();
}

void bm::AIController::SetNextInput()
{
	if (!m_Path.empty())
	{
		m_EntityInput.direction = m_Path.back();
		m_Path.pop_back();
	}
}

//===================================================================
// PathingCommands
//===================================================================

//RandomPathingCommand================

bm::RandomPathingCommand::RandomPathingCommand(dae::GameObject& entity, std::vector<glm::ivec2>& path, int minTiles, int maxTiles)
	: m_Entity{ entity }
	, m_Path{ path }
	, m_MinTiles{ minTiles }
	, m_MaxTiles{ maxTiles }
{
}

void bm::RandomPathingCommand::Execute()
{
	auto& pathingSystem = BMServiceLocator::GetPathfinderSystem();
	auto& randomSystem = dae::ServiceLocator::GetRandomSystem();

	m_Path.clear();
	m_Path = pathingSystem.GetRandomPath(m_Entity.GetWorldPos(), randomSystem.GetRandomInt(m_MinTiles, m_MaxTiles));
	pathingSystem.ConvertPathToDirections(m_Path);	//convert the path to directions and reverse the vector
}

//PathToTargetCommand================

bm::PathToTargetCommand::PathToTargetCommand(dae::GameObject& entity, std::vector<glm::ivec2>& path, std::function<dae::GameObjectHandle()> targetFunc, std::unique_ptr<dae::Command>&& backupCommand)
	: m_Entity{ entity }
	, m_Target{}
	, m_Path{ path }
	, m_TargetFunc{ std::move(targetFunc) }
{
	backupCommand;
}

void bm::PathToTargetCommand::Execute()
{
	m_Path.clear();

	if (!m_Target)	//no target set
		m_Target = m_TargetFunc();
	if (!m_Target)	//no target found
	{
		return;
	}

	//try using the target 
	auto& pathingSystem = BMServiceLocator::GetPathfinderSystem();
	m_Path = pathingSystem.FindPath(m_Entity.GetWorldPos(), m_Target->GetWorldPos());
	if (m_Path.empty())	//no path found
		return;

	pathingSystem.ConvertPathToDirections(m_Path);	//convert the path to directions and reverse the vector
}

//Helper functions===================

#include <Scene.h>

dae::GameObjectHandle bm::GetPlayer()	//used as the target function for the AIController's PathToTargetCommand
{
	//Gets all the players in the scene and picks a random one

	auto* currentScene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();

	if (!currentScene)
	{
		std::cout << "Warning: No current scene found\n";
		return {};
	}

	auto playerHandles = currentScene->GetObjectByID(bm::PLAYER_GOBJID);
	if (playerHandles.empty())
	{
		return {};
	}

	auto& randomSystem = dae::ServiceLocator::GetRandomSystem();
	int playerIndex = randomSystem.GetRandomInt(0, static_cast<int>(playerHandles.size()) - 1);
	return playerHandles[playerIndex];
}
