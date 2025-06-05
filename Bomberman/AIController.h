#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <vector>
#include <glm.hpp>
#include <functional>
#include <memory>

#include <GameObjectHandle.h>

#include "EntityController.h"
#include "Command.h"

namespace bm
{
	class AIController final : public EntityController
	{
	public:

		enum class Intelligence
		{
			low,
			normal
		};

		AIController(Intelligence intelligence, dae::GameObject& entity);

		void Update(EntityCondition condition) override;

	private:

		void SetNewPath();
		void SetRandomPath();
		void SetNextInput();

		//==================

		std::vector<glm::ivec2> m_Path{};
		std::unique_ptr<dae::Command> m_pPathingCommand{};
		std::unique_ptr<dae::Command> m_pRandomPathingCommand{}; //used when being blocked by something (bomb)
	};

	//====================================================================================

	class RandomPathingCommand final : public dae::Command
	{
	public:
		RandomPathingCommand(dae::GameObject& entity, std::vector<glm::ivec2>& path, int minTiles, int maxTiles);
		void Execute() override;
	private:
		dae::GameObject& m_Entity;	//used to get the position of the entity
		std::vector<glm::ivec2>& m_Path;
		int m_MinTiles;
		int m_MaxTiles;
	};

	class PathToTargetCommand final : public dae::Command
	{
	public:
		PathToTargetCommand(dae::GameObject& entity, std::vector<glm::ivec2>& path, std::function<dae::GameObjectHandle()> targetFunc, std::unique_ptr<dae::Command>&& backupCommand);
		void Execute() override;
	private:
		dae::GameObject& m_Entity;	//used to get the position of the entity (this)
		dae::GameObjectHandle m_Target;	//used to get the position of the target entity
		std::vector<glm::ivec2>& m_Path;
		std::function<dae::GameObjectHandle()> m_TargetFunc;	//function to get the target object
		//std::unique_ptr<dae::Command> m_BackupCommand;	//if the pathfinding fails, this command will be executed
	};

	dae::GameObjectHandle GetPlayer();
}

#endif // !AICONTROLLER_H
