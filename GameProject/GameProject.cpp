
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <Scene.h>
#include <SceneManager.h>
#include <GameObject.h>
#include <InputManager.h>
#include <EngineComponents.h>
#include <Texture.h>
#include <ServiceLocator.h>

#include "GameComponents.h"

//todo delete statics
static dae::TextureEntry g_BackgroundTextureEntry{ "background.tga" };
static dae::TextureEntry g_PlayerIcon{ "playerIcon.png" };
static dae::TextureEntry g_BalloomIcon{ "balloonIcon.png" };
static dae::TextureEntry g_Bomberman{ "Bomberman.png" };
static dae::FontEntry g_PixelFont{ "KenneyPixel.ttf" };

void LoadDemo() {};
void RenderTest();

int main(int, char* []) 
{
	dae::Window window{ .title = "Minigin V2", .w = 256, .h = 240, .renderScale = 2.f };

	dae::Minigin engine("../Data/", window);
	dae::ServiceLocator::GetSoundSystem().SetGlobalVolume(0.1f);
	engine.Run(&RenderTest);
	return 0;
}

void RenderTest()
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
	rendComp->SetRenderSize({200, 100});
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
	tranComp->SetLocalPosition(200, 200);
	rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	rendComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	auto* spriteComp = go->AddComponent<dae::SpriteComp>();
	spriteComp->LoadTexture(g_Bomberman);
	spriteComp->AddSpriteEntry(dae::SpriteEntry("WalkRight", {0, 16, 64, 16}, 4, 1));
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

/*
void LoadDemo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background=============================
	auto go = std::make_unique<dae::GameObject>();
	auto rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->LoadTexture(std::string("background.tga"));
	rendComp->LoadImageTexture(g_BackgroundTextureEntry);
	scene.Add(std::move(go));

	//title==================================
	auto titleFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<dae::RenderComp>();
	auto tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(50, 20);
	auto textComp = go->AddComponent<dae::TextComp>(titleFont);
	textComp->SetText("Programming 4 Assignment");
	scene.Add(std::move(go));

	//Character01=======================================================================================
	go = std::make_unique<dae::GameObject>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(200, 200);
	rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->LoadTexture(std::string("playerIcon.png"));
	rendComp->LoadImageTexture(g_PlayerIcon);
	go->AddComponent<GameActorComp>(50.f, 0);
	auto* healtComp = go->AddComponent<HealthComp>(3);
	auto* scoreComp = go->AddComponent<ScoreComp>();

	scene.Add(std::move(go));

	//Character01_UI=========================
	auto uiFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//HealthUI
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComp>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(20, 100);
	textComp = go->AddComponent<dae::TextComp>(uiFont);
	go->AddComponent<UIHealthComp>(healtComp);
	//ScoreUI
	auto go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<dae::RenderComp>();
	tranComp = go2->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(0, 15);
	textComp = go2->AddComponent<dae::TextComp>(uiFont);
	go2->AddComponent<UIScoreComp>(scoreComp);

	go2->SetParent(go.get(), false);
	scene.Add(std::move(go));
	scene.Add(std::move(go2));

	//Character02=======================================================================================
	go = std::make_unique<dae::GameObject>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(220, 200);
	rendComp = go->AddComponent<dae::RenderComp>();
	rendComp->LoadTexture(std::string("balloonIcon.png"));
	rendComp->LoadImageTexture(g_BalloomIcon);
	go->AddComponent<GameActorComp>(100.f, 1);
	healtComp = go->AddComponent<HealthComp>(3);
	scoreComp = go->AddComponent<ScoreComp>();

	scene.Add(std::move(go));

	//Character02_UI=========================
	//HealthUI
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComp>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(20, 140);
	textComp = go->AddComponent<dae::TextComp>(uiFont);
	go->AddComponent<UIHealthComp>(healtComp);
	//ScoreUI
	go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<dae::RenderComp>();
	tranComp = go2->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(0, 15);
	textComp = go2->AddComponent<dae::TextComp>(uiFont);
	go2->AddComponent<UIScoreComp>(scoreComp);

	go2->SetParent(go.get(), false);
	scene.Add(std::move(go));
	scene.Add(std::move(go2));
	//==================================================================================================

	//Keyboard controls======================

	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<dae::RenderComp>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(20, 60);
	textComp = go->AddComponent<dae::TextComp>(uiFont);
	textComp->SetText("Use WASD to move bomberman, C to inflict damage, Z and X to pick up pellets");
	scene.Add(std::move(go));

	//Gamepad controls=======================
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::RenderComp>();
	tranComp = go->GetComponent<dae::TransformComp>();
	tranComp->SetLocalPosition(20, 75);
	textComp = go->AddComponent<dae::TextComp>(uiFont);
	textComp->SetText("Use D-pad to move balloon, X to inflict damage, A and B to pick up pellets");
	scene.Add(std::move(go));
};
*/

/*
void LoadDemo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background=============================
	auto go = std::make_unique<dae::GameObject>();
	auto rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("background.tga");
	scene.Add(std::move(go));

	//title==================================
	auto titleFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	auto tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(50, 20);
	auto textComp = go->AddComponent<TextComp>(titleFont);
	textComp->SetText("Programming 4 Assignment");
	scene.Add(std::move(go));

	//Character01=======================================================================================
	go = std::make_unique<dae::GameObject>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(200, 200);
	rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("playerIcon.png");
	go->AddComponent<GameActorComp>(50.f, 0);
	auto* healtComp = go->AddComponent<HealthComp>(3);
	auto* scoreComp = go->AddComponent<ScoreComp>();

	scene.Add(std::move(go));

	//Character01_UI=========================
	auto uiFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//HealthUI
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 100);
	textComp = go->AddComponent<TextComp>(uiFont);
	go->AddComponent<UIHealthComp>(healtComp);
	//ScoreUI
	auto go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<RenderComp>();
	tranComp = go2->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(0, 15);
	textComp = go2->AddComponent<TextComp>(uiFont);
	go2->AddComponent<UIScoreComp>(scoreComp);

	go2->SetParent(go.get(), false);
	scene.Add(std::move(go));
	scene.Add(std::move(go2));

	//Character02=======================================================================================
	go = std::make_unique<dae::GameObject>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(220, 200);
	rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("balloonIcon.png");
	go->AddComponent<GameActorComp>(100.f, 1);
	healtComp = go->AddComponent<HealthComp>(3);
	scoreComp = go->AddComponent<ScoreComp>();

	scene.Add(std::move(go));

	//Character02_UI=========================
	//HealthUI
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 140);
	textComp = go->AddComponent<TextComp>(uiFont);
	go->AddComponent<UIHealthComp>(healtComp);
	//ScoreUI
	go2 = std::make_unique<dae::GameObject>();
	go2->AddComponent<RenderComp>();
	tranComp = go2->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(0, 15);
	textComp = go2->AddComponent<TextComp>(uiFont);
	go2->AddComponent<UIScoreComp>(scoreComp);

	go2->SetParent(go.get(), false);
	scene.Add(std::move(go));
	scene.Add(std::move(go2));
	//==================================================================================================

	//Keyboard controls======================

	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 60);
	textComp = go->AddComponent<TextComp>(uiFont);
	textComp->SetText("Use WASD to move bomberman, C to inflict damage, Z and X to pick up pellets");
	scene.Add(std::move(go));

	//Gamepad controls=======================
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 75);
	textComp = go->AddComponent<TextComp>(uiFont);
	textComp->SetText("Use D-pad to move balloon, X to inflict damage, A and B to pick up pellets");
	scene.Add(std::move(go));
}
*/

