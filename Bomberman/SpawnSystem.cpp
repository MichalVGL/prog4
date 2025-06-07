#include "SpawnSystem.h"

#include <Scene.h>
#include <SceneManager.h>

#include "BMServiceLocator.h"
#include "BMGameDefines.h"
#include "ObjectConstructions.h"
#include "BMComponents.h"

void bm::SpawnSystem::SpawnLevelStructures(int walls)
{
	//todo implement
	walls;
}

dae::GameObjectHandle bm::SpawnSystem::SpawnBomb(glm::vec2 pos)
{
	auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
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
	auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
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
	auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (!scene)
		return;
	auto go = bm::RenderGOBJ(UPGRADE_GOBJID);

	auto* transform = go->GetComponent<dae::TransformComp>();
	transform->SetLocalPosition(pos);

	go->AddComponent<bm::TileCollisionComp>();
	go->AddComponent<bm::UpgradeComp>(type);

	scene->Add(std::move(go));
}
