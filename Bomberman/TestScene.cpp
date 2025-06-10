#include "TestScene.h"

#include <EngineComponents.h>
#include <filesystem>
#include <ServiceLocator.h>
#include <Utils.h>
#include <memory>

#include <ServiceLocator.h>

#include "BMGameDefines.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "BMServiceLocator.h"
#include "TileSystem.h"
#include "PlayerController.h"
#include "AIController.h"

void bm::TestScene::Load()
{
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	renderSystem.SetBackgroundColor({ .r = 156, .g = 156, .b = 156, .a = 255 });

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.SetBounds({ 0, 0, 496, 240 });
	

	//Level==================================
	bm::BMServiceLocator::RegisterTileSystem(std::make_unique<bm::Level_TileSystem>());

	
	//Timer==================================
	auto go = bm::GOBJ("UI");
	go->AddComponent<dae::FollowCameraComp>();
	auto* uiGO = Add(std::move(go));

	go = bm::RenderGOBJ("TestTimer");
	go->SetLocalPosition({ 20.f, 220.f });
	auto textComp = go->AddComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(bm::MAIN_FONT);
	auto timerComp = go->AddComponent<bm::TimerComp>(30.f, true);
	timerComp->SetFormatFunction([](float t) { return std::format("Time left: {:.0f} h", t); });

	go->SetParent(uiGO, true);

	Add(std::move(go));

	//Player============================================================================
	go = bm::SpriteGOBJ(bm::PLAYER_GOBJID, 2);
	auto* spriteComp = go->GetComponent<dae::SpriteComp>();
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
	transComp->SetLocalPosition(24, 24);

	auto* pPlayer = Add(std::move(go));
	cameraSystem.AddGObjSubject(pPlayer);
	m_Player = pPlayer;

	//Enemy=============================================================================
	go = bm::SpriteGOBJ(bm::ENEMY_GOBJID, 1);
	spriteComp = go->GetComponent<dae::SpriteComp>();
	spriteComp->LoadTexture(bm::ENEMY_TEXTURE);
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveDown", { 0, bm::TILE_SIZE * 3, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveUp", { bm::TILE_SIZE * 4, bm::TILE_SIZE * 3, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("MoveLeft", { bm::TILE_SIZE * 4, bm::TILE_SIZE * 3, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->AddSpriteEntry(dae::SpriteEntry("Death", { bm::TILE_SIZE * 8, bm::TILE_SIZE * 3, bm::TILE_SIZE * 5, bm::TILE_SIZE }, 5, 1, false));
	auto pAIController = std::make_unique<bm::AIController>(bm::AIController::Intelligence::normal, *go);
	go->AddComponent<bm::EntityComp>(bm::ENTITYSTATS_SLOW, std::move(pAIController));
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(88, 88);
	go->AddComponent<dae::SimpleCollisionComp>();	//add collision detection to the gameobject detecting the player
	go->AddComponent<bm::EnemyComp>();

	go->AddComponent<bm::ScoreComp>(100);	//add score component to the enemy, so it can give score when killed

	//cameraSystem.AddGObjSubject(scene.Add(std::move(go)));
	Add(std::move(go));

	//Wall test=========================================================================
	go = bm::SpriteGOBJ("Wall");
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(72, 56);
	go->AddComponent<bm::WallComp>();

	Add(std::move(go));

	//Wall2 upgrade=====================================================================
	go = bm::SpriteGOBJ("Wall");
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(104, 56);
	go->AddComponent<bm::WallComp>(bm::ContainedObject::upgrade);

	Add(std::move(go));

	//Bomb test=========================================================================
	go = bm::SpriteGOBJ("Bomb");
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(56, 56);
	go->AddComponent<bm::TimerComp>();
	go->AddComponent<bm::BombComp>();

	Add(std::move(go));

	//Upgrade test======================================================================
	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	spawnSystem.SpawnUpgrade({ 56, 104 }, bm::UpgradeType::bombRange);
	spawnSystem.SpawnUpgrade({ 56, 120 }, bm::UpgradeType::bombCount);
	spawnSystem.SpawnUpgrade({ 88, 104 }, bm::UpgradeType::remoteDetonator);
	
}

void bm::TestScene::Exit()
{
}

std::unique_ptr<dae::Scene> bm::TestScene::UpdateScene(float )
{
	if (m_Player.Get() == nullptr)
		return std::make_unique<TestScene>();

    return nullptr;
}
