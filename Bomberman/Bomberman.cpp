
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <Scene.h>
#include <EngineComponents.h>

#include "BMGameDefines.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"


//todo delete statics
static dae::TextureEntry g_BackgroundTextureEntry{ "background.tga" };
//static dae::TextureEntry g_PlayerIcon{ "playerIcon.png" };
//static dae::TextureEntry g_BalloomIcon{ "balloonIcon.png" };
static dae::TextureEntry g_Bomberman{ "Bomberman.png" };
static dae::FontEntry g_PixelFont{ "KenneyPixel.ttf" };

void Test();

void LevelTest();

int main(int, char* []) {

	dae::Window window{ .title = "Bomberman", .w = 256, .h = 240, .renderScale = 2.f };

	dae::Minigin engine("../Data/", window);
	dae::ServiceLocator::GetSoundSystem().SetGlobalVolume(0.1f);
	engine.Run(&LevelTest);
	return 0;
}

void LevelTest()
{
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	renderSystem.SetBackgroundColor({.r = 156, .g = 156, .b = 156, .a = 255});

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Level==================================
	bm::MakeLevel(scene);

	//Timer==================================
	auto go = bm::RenderGOBJ("TestTimer");
	go->SetLocalPosition({ 20.f, 220.f });
	auto textComp = go->AddComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(g_PixelFont);
	auto timerComp = go->AddComponent<bm::TimerComp>(20.f, true);
	timerComp->SetFormatFunction([](float t) { return std::format("Timer: {:.0f}", t); });

	scene.Add(std::move(go));

	//Character01=======================================================================================
	go = std::make_unique<dae::GameObject>("Bomberman");
	auto tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(100, 100);
	auto rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	rendComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	auto* spriteComp = go->AddComponent<dae::SpriteComp>();
	spriteComp->LoadTexture(g_Bomberman);
	spriteComp->AddSpriteEntry(dae::SpriteEntry("WalkRight", { 0, bm::TILE_SIZE, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->SetSpriteEntry(dae::SpriteId("WalkRight"));
	spriteComp->SetFPS(6.f);
	spriteComp->FlipHorizontal(true);
	go->AddComponent<GameActorComp>(50.f, 0);
	auto* healtComp = go->AddComponent<HealthComp>(3);
	auto* scoreComp = go->AddComponent<ScoreComp>();
	healtComp;
	scoreComp;
	scene.Add(std::move(go));

}

void Test()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background=============================
	auto go = std::make_unique<dae::GameObject>();
	auto rendComp = go->AddComponent<dae::RenderComp>();
	auto tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(128, 120);	//320 240
	rendComp->LoadImageTexture(g_BackgroundTextureEntry);
	rendComp->SetSrcRect(dae::Rect{ 0, 0, 640, 480 });
	rendComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	rendComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	rendComp->SetAngle(45);
	rendComp->SetRenderSize({ 200, 100 });
	scene.Add(std::move(go));

	//title==================================
	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->SetHorizontalFlip(false);
	rendComp->SetVerticalFlip(false);
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(5, 200);
	auto textComp = go->AddComponent<dae::TextComp>();
	textComp->SetFont(g_PixelFont);
	textComp->SetText("Programming 4 Assignment");
	scene.Add(std::move(go));

	//Character01=======================================================================================
	go = std::make_unique<dae::GameObject>("Bomberman");
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(100, 100);
	rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	rendComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	auto* spriteComp = go->AddComponent<dae::SpriteComp>();
	spriteComp->LoadTexture(g_Bomberman);
	spriteComp->AddSpriteEntry(dae::SpriteEntry("WalkRight", { 0, bm::TILE_SIZE, bm::TILE_SIZE * 4, bm::TILE_SIZE }, 4, 1));
	spriteComp->SetSpriteEntry(dae::SpriteId("WalkRight"));
	spriteComp->SetFPS(6.f);
	spriteComp->FlipHorizontal(true);
	go->AddComponent<GameActorComp>(50.f, 0);
	auto* healtComp = go->AddComponent<HealthComp>(3);
	auto* scoreComp = go->AddComponent<ScoreComp>();

	scene.Add(std::move(go));

	//Character01_UI=========================
	//HealthUI
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComp>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(20, 100);
	textComp = go->AddComponent<dae::TextComp>();
	textComp->SetFont(g_PixelFont);
	textComp->SetSize(16);
	go->AddComponent<UIHealthComp>(healtComp);
	//ScoreUI
	auto go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<dae::RenderComp>();
	tranComp = go2->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(0, 15);
	textComp = go2->AddComponent<dae::TextComp>();
	textComp->SetFont(g_PixelFont);
	textComp->SetSize(16);
	go2->AddComponent<UIScoreComp>(scoreComp);

	go2->SetParent(go.get(), false);
	scene.Add(std::move(go));
	scene.Add(std::move(go2));
}