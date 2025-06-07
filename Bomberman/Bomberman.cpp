
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <Scene.h>
#include <EngineComponents.h>
#include <filesystem>
#include <ServiceLocator.h>

#include "BMGameDefines.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "BMServiceLocator.h"
#include "TileSystem.h"
#include "PlayerController.h"
#include "AIController.h"


//todo delete statics
//static dae::TextureEntry g_BackgroundTextureEntry{ "background.tga" };
//static dae::TextureEntry g_PlayerIcon{ "playerIcon.png" };
//static dae::TextureEntry g_BalloomIcon{ "balloonIcon.png" };
//static dae::TextureEntry g_Bomberman{ "Bomberman.png" };
static dae::FontEntry g_PixelFont{ "KenneyPixel.ttf" };

void Test();

void LevelTest();

std::filesystem::path GetDataPath()
{
	// Preferred path (e.g., when running from Visual Studio)
	std::filesystem::path vsPath = "../" DATA_FOLDER_PATH;
	if (std::filesystem::exists(vsPath))
		return vsPath;

	// Fallback (e.g., when running the .exe directly)
	std::filesystem::path exePath = DATA_FOLDER_PATH;
	if (std::filesystem::exists(exePath))
		return exePath;

	std::cout << "Data folder not found.\n";
	throw std::runtime_error("Data folder not found.");
}

int main(int, char* []) {

	dae::Window window{ .title = "Bomberman", .w = 256, .h = 240, .renderScale = 3.f };

	dae::Minigin engine(GetDataPath().string(), window);
	dae::ServiceLocator::GetSoundSystem().SetGlobalVolume(0.1f);
	engine.Run(&LevelTest);
	return 0;
}

void LevelTest()
{
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	renderSystem.SetBackgroundColor({.r = 156, .g = 156, .b = 156, .a = 255});

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.SetBounds({ 0, 0, 496, 240 });

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Level==================================
	bm::BMServiceLocator::RegisterTileSystem(std::make_unique<bm::Level_TileSystem>(scene));

	//Timer==================================
	auto go = bm::RenderGOBJ("TestTimer");
	go->SetLocalPosition({ 20.f, 220.f });
	auto textComp = go->AddComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(g_PixelFont);
	auto timerComp = go->AddComponent<bm::TimerComp>(30.f, true);
	timerComp->SetFormatFunction([](float t) { return std::format("Time left: {:.0f} h", t); });

	scene.Add(std::move(go));

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
	
	cameraSystem.AddGObjSubject(scene.Add(std::move(go)));

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

	cameraSystem.AddGObjSubject(scene.Add(std::move(go)));

	//Wall test=========================================================================
	go = bm::SpriteGOBJ("Wall");
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(72, 56);
	go->AddComponent<bm::WallComp>();

	scene.Add(std::move(go));

	//Bomb test=========================================================================
	go = bm::SpriteGOBJ("Bomb");
	transComp = go->GetComponent<dae::TransformComp>();
	transComp->SetLocalPosition(56, 56);
	go->AddComponent<bm::TimerComp>();
	go->AddComponent<bm::BombComp>();

	scene.Add(std::move(go));

	//Upgrade test======================================================================
	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	spawnSystem.SpawnUpgrade({ 56, 104 }, bm::UpgradeType::bombRange);
	spawnSystem.SpawnUpgrade({ 56, 120 }, bm::UpgradeType::bombCount);
	spawnSystem.SpawnUpgrade({ 88, 104 }, bm::UpgradeType::remoteDetonator);


}

void Test()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//
	////background=============================
	//auto go = std::make_unique<dae::GameObject>();
	//auto rendComp = go->AddComponent<dae::RenderComp>();
	//auto tranComp = go->GetComponent<dae::TransformComp>();
	//tranComp->SetLocalPosition(128, 120);	//320 240
	//rendComp->LoadImageTexture(g_BackgroundTextureEntry);
	//rendComp->SetSrcRect(dae::Rect{ 0, 0, 640, 480 });
	//rendComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	//rendComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	//rendComp->SetAngle(45);
	//rendComp->SetRenderSize({ 200, 100 });
	//scene.Add(std::move(go));
	//
	////title==================================
	//go = std::make_unique<dae::GameObject>();
	//rendComp = go->AddComponent<dae::RenderComp>();
	//rendComp->SetHorizontalFlip(false);
	//rendComp->SetVerticalFlip(false);
	//tranComp = go->GetComponent<dae::TransformComp>();
	//tranComp->SetLocalPosition(5, 200);
	//auto textComp = go->AddComponent<dae::TextComp>();
	//textComp->SetFont(g_PixelFont);
	//textComp->SetText("Programming 4 Assignment");
	//scene.Add(std::move(go));
}