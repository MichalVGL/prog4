#include "SpawnSystem.h"

#include <Scene.h>
#include <ServiceLocator.h>

#include "BMServiceLocator.h"
#include "BMGameDefines.h"
#include "ObjectConstructions.h"
#include "BMComponents.h"
#include "PlayerController.h"
#include "AIController.h"
#include "EnemyTypes.h"

void bm::SpawnSystem::SpawnLevelWalls(int totalAmount, int powerUpWalls, std::vector<TileComp*> tileToIgnore)
{
	auto& tileSystem = bm::BMServiceLocator::GetTileSystem();

	auto availableTiles = tileSystem.GetAllWalkableTiles();

	//remove the ignored tiles
	for (auto* tile : tileToIgnore)
	{
		availableTiles.erase(std::remove(availableTiles.begin(), availableTiles.end(), tile), availableTiles.end());
	}

	//spawn the door
	if (availableTiles.empty())
	{
		std::cout << std::format("Warning: cannot spawn a door, no available tiles.");
		return;
	}
	else
	{
		auto randomIndex = dae::ServiceLocator::GetRandomSystem().GetRandomInt(0, static_cast<int>(availableTiles.size()) - 1);
		auto* tile = availableTiles.at(randomIndex);
		if (tile)
		{
			SpawnWall(tile->GetPosition(), ContainedObject::door);
			availableTiles.erase(availableTiles.begin() + randomIndex);
			totalAmount--;
		}
		else
		{
			std::cout << std::format("Error: didn't spawn a door, tile was invalid");
			return;
		}
	}


	//spawn the powered up walls
	for (int i = 0; i < powerUpWalls; ++i)
	{
		if (availableTiles.empty())
		{
			std::cout << std::format("Warning: cannot spawn the amount of powered walls requested, no more available tiles.");
			break;
		}
		auto randomIndex = dae::ServiceLocator::GetRandomSystem().GetRandomInt(0, static_cast<int>(availableTiles.size()) - 1);
		auto* tile = availableTiles.at(randomIndex);
		if (tile)
		{
			SpawnWall(tile->GetPosition(), ContainedObject::upgrade);
			availableTiles.erase(availableTiles.begin() + randomIndex); //remove the tile so it can't be used again
			totalAmount--;
		}
	}

	//spawn the random walls
	for (int i = 0; i < totalAmount; ++i)
	{
		if (availableTiles.empty())
		{
			std::cout << std::format("Warning: cannot spawn the amount of walls requested, no more available tiles.");
			break;
		}

		auto randomIndex = dae::ServiceLocator::GetRandomSystem().GetRandomInt(0, static_cast<int>(availableTiles.size()) - 1);
		auto* tile = availableTiles.at(randomIndex);
		if (tile)
		{
			SpawnWall(tile->GetPosition(), ContainedObject::none);
			availableTiles.erase(availableTiles.begin() + randomIndex); //remove the tile so it can't be used again
		}
	}
}

void bm::SpawnSystem::SpawnEnemies(int amount, std::vector<EnemyType> types, std::vector<TileComp*> tileToIgnore)
{
	if (types.empty())
	{
		std::cout << std::format("Error: no enemy types provided for spawning enemies.");
		return;
	}

	auto& tileSystem = bm::BMServiceLocator::GetTileSystem();

	auto availableTiles = tileSystem.GetAllWalkableTiles();

	//remove the ignored tiles
	for (auto* tile : tileToIgnore)
	{
		availableTiles.erase(std::remove(availableTiles.begin(), availableTiles.end(), tile), availableTiles.end());
	}

	//remove tiles that dont have a walkable neighbour
	availableTiles.erase(
		std::remove_if(
			availableTiles.begin(),
			availableTiles.end(),
			[](TileComp* tile) {
				// Check all four neighbors
				auto isWalkable = [](TileComp* neighbor) {
					return neighbor && neighbor->IsWalkable();
					};
				return !(
					isWalkable(tile->GetUpTile()) ||
					isWalkable(tile->GetRightTile()) ||
					isWalkable(tile->GetDownTile()) ||
					isWalkable(tile->GetLeftTile())
					);
			}
		),
		availableTiles.end()
	);

	//spawn the enemies
	for (int i = 0; i < amount; ++i)
	{
		if (availableTiles.empty())
		{
			std::cout << std::format("Warning: cannot spawn the amount of enemies requested, no more available tiles.");
			break;
		}
		auto randomIndex = dae::ServiceLocator::GetRandomSystem().GetRandomInt(0, static_cast<int>(availableTiles.size()) - 1);
		auto* tile = availableTiles.at(randomIndex);
		if (tile)
		{
			auto type = types.at(dae::ServiceLocator::GetRandomSystem().GetRandomInt(0, static_cast<int>(types.size()) - 1));	//get random type from the types vector
			SpawnEnemy(tile->GetPosition(), type);
			availableTiles.erase(availableTiles.begin() + randomIndex); //remove the tile so it can't be used again
		}
	}

}

//=================================================================================================

void bm::SpawnSystem::SpawnPlayer()
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();

	auto go = bm::SpriteGOBJ(bm::PLAYER_GOBJID, 2);
	auto* spriteComp = go->GetComponent<dae::SpriteComp>();
	spriteComp->SetFPS(GLOBAL_FPS);
	spriteComp->LoadTexture(bm::PLAYER_TEXTURE);
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveDown", { 0, bm::TILE_SIZE * 3, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveUp", { 0, bm::TILE_SIZE * 2, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveLeft", { 0, bm::TILE_SIZE * 1, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("Death", { 0, 0, bm::TILE_SIZE * 7, bm::TILE_SIZE }, 7, 1, false));
	go->AddComponent<bm::BombDeployerComp>();
	auto* entityComp = go->AddComponent<bm::EntityComp>(bm::ENTITYSTATS_MEDIUM, std::make_unique<bm::PlayerController>());
	entityComp->SetCommand1(std::make_unique<bm::DeployCommand>(*go));
	entityComp->SetCommand2(std::make_unique<bm::DetonateCommand>(*go));
	auto* transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(static_cast<float>(bm::PLAYER_START_TILE.x * bm::TILE_SIZE + bm::TILE_SIZE / 2)
		, static_cast<float>(bm::PLAYER_START_TILE.y * bm::TILE_SIZE + bm::TILE_SIZE / 2));

	go->AddComponent<bm::BombermanComp>();

	auto* pPlayer = scene->Add(std::move(go));
	cameraSystem.AddGObjSubject(pPlayer);
}

void bm::SpawnSystem::SpawnEnemy(glm::vec2 pos, EnemyType type)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;

	auto go = bm::SpriteGOBJ(bm::ENEMY_GOBJID, 1);
	auto spriteComp = go->GetComponent<dae::SpriteComp>();
	spriteComp->LoadTexture(bm::ENEMY_TEXTURE);
	spriteComp->SetFPS(GLOBAL_FPS / 2);

	//visuals
	int tileOffset = [&]() -> int
		{
			// represents the offset on the sprite
			switch (type)
			{
			case bm::EnemyType::balloom: return 3;
			case bm::EnemyType::oneal: return 2;
			case bm::EnemyType::doll: return 1;
			case bm::EnemyType::minvo: return 0;
			default:
				return 0;
			}
		}();
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveDown", { 0, bm::TILE_SIZE * tileOffset, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveUp", { bm::TILE_SIZE * 4, bm::TILE_SIZE * tileOffset, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveLeft", { bm::TILE_SIZE * 4, bm::TILE_SIZE * tileOffset, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("Death", { bm::TILE_SIZE * 8, bm::TILE_SIZE * tileOffset, bm::TILE_SIZE * 5, bm::TILE_SIZE }, 5, 1, false));

	//controller
	AIController::Intelligence intelligence = [&]() -> AIController::Intelligence
		{
			switch (type)
			{
			case bm::EnemyType::balloom:
			case bm::EnemyType::doll:
				return AIController::Intelligence::low;
			case bm::EnemyType::oneal:
			case bm::EnemyType::minvo:
				return AIController::Intelligence::normal;
			default: return AIController::Intelligence::low;
			}
		}();
	auto pAIController = std::make_unique<bm::AIController>(intelligence, *go);

	//entity comp
	EntityStats stats = [&]() -> EntityStats
		{
			switch (type)
			{
			case bm::EnemyType::balloom:
				return bm::ENTITYSTATS_SLOW;
			case bm::EnemyType::oneal:
			case bm::EnemyType::doll:
				return bm::ENTITYSTATS_MEDIUM;
			case bm::EnemyType::minvo:
				return bm::ENTITYSTATS_FAST;
			default: return bm::ENTITYSTATS_SLOW;
			}
		}();
	go->AddComponent<bm::EntityComp>(stats, std::move(pAIController));

	auto transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(pos.x, pos.y);

	go->AddComponent<dae::SimpleCollisionComp>();
	go->AddComponent<bm::EnemyComp>();

	int score = [&]() -> int
		{
			switch (type)
			{
			case bm::EnemyType::balloom:
				return BALLOOM_SCORE;
			case bm::EnemyType::oneal:
				return ONEAL_SCORE;
			case bm::EnemyType::doll:
				return DOLL_SCORE;
			case bm::EnemyType::minvo:
				return MINVO_SCORE;
			default: return 0;
			}
		}();

	go->AddComponent<bm::ScoreComp>(score);

	scene->Add(std::move(go));
}

void bm::SpawnSystem::SpawnPlayerEnemy()
{
	//todo implement
}

//=================================================================================================

void bm::SpawnSystem::SpawnWall(glm::vec2 pos, ContainedObject containedObject)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;

	auto go = bm::SpriteGOBJ("Wall");
	auto* transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(pos.x, pos.y);
	go->AddComponent<bm::WallComp>(containedObject);

	scene->Add(std::move(go));
}

dae::GameObjectHandle bm::SpawnSystem::SpawnBomb(glm::vec2 pos)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	auto& tileSystem = bm::BMServiceLocator::GetTileSystem();
	auto* currentTile = tileSystem.GetTileFromWorldPos(pos);
	if (!scene || !currentTile)
		return dae::GameObjectHandle();

	if (currentTile->IsWalkable() == false or
		currentTile->HasTileMod() == true)
	{
		return dae::GameObjectHandle();	//cannot spawn a bomb on a non-walkable tile or a tile that already has a mod
	}

	auto go = bm::SpriteGOBJ(BOMB_GOBJID);
	auto* transComp = go->GetComponent<dae::TransformComp>();
	auto tilePos = currentTile->GetPosition();
	transComp->SetLocalPosition(tilePos.x, tilePos.y);
	go->AddComponent<bm::TimerComp>();
	go->AddComponent<bm::BombComp>();

	return dae::GameObjectHandle(scene->Add(std::move(go)));
}

void bm::SpawnSystem::SpawnFire(glm::vec2 pos, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;

	auto go = bm::SpriteGOBJ(FIRE_GOBJID);
	auto* transform = go->GetComponent<dae::TransformComp>();
	transform->SetLocalPosition(pos);
	go->AddComponent<bm::TileCollisionComp>();
	go->AddComponent<bm::FireComp>(targets, direction, spreadAmount);

	scene->Add(std::move(go));
}

void bm::SpawnSystem::SpawnUpgrade(glm::vec2 pos, UpgradeType type)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;
	auto go = bm::RenderGOBJ(UPGRADE_GOBJID);

	auto* transform = go->GetComponent<dae::TransformComp>();
	transform->SetLocalPosition(pos);

	go->AddComponent<bm::TileCollisionComp>();
	go->AddComponent<bm::UpgradeComp>(type);

	scene->Add(std::move(go));
}

void bm::SpawnSystem::SpawnRandomUpgrade(glm::vec2 pos)
{
	auto& randomSystem = dae::ServiceLocator::GetRandomSystem();
	auto& upgradeSystem = bm::BMServiceLocator::GetUpgradeSystem();

	int randomType = [&]() -> int
		{
			if (!upgradeSystem.IsRemoteActive())
			{
				return randomSystem.GetRandomInt(0, static_cast<int>(UpgradeType::count) - 1);	//all types allowed
			}
			else //prevent remote from being picked
			{
				int rnd{};
				do
				{
					rnd = randomSystem.GetRandomInt(0, static_cast<int>(UpgradeType::count) - 1);
				} while (rnd == static_cast<int>(UpgradeType::remoteDetonator));
				return rnd;
			}
		}();

	SpawnUpgrade(pos, static_cast<UpgradeType>(randomType));
}

void bm::SpawnSystem::SpawnDoor(glm::vec2 pos)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;
	auto go = bm::RenderGOBJ(DOOR_GOBJID);

	auto* transform = go->GetComponent<dae::TransformComp>();
	transform->SetLocalPosition(pos);

	go->AddComponent<bm::TileCollisionComp>();
	go->AddComponent<bm::DoorComp>();

	scene->Add(std::move(go));
}

void bm::SpawnSystem::SpawnTempText(glm::vec2 pos, const std::string& text, float time, int size)
{
	auto* scene = dae::ServiceLocator::GetSceneSystem().GetCurrentScene();
	if (!scene)
		return;

	auto go = bm::TextGOBJ("TempText", 3);
	auto* textComp = go->GetComponent<dae::TextComp>();
	textComp->SetText(text);
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(size);

	go->AddComponent<dae::AutoDestroyComp>(time);

	go->GetComponent<dae::TransformComp>()->SetLocalPosition(pos);;

	scene->Add(std::move(go));
}
