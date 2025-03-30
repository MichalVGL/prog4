
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
#include <ResourceManager.h>
#include <EngineComponents.h>

#include "GameComponents.h"

void LoadDemo();

//todo, change engine classes to be in namespace dae

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(&LoadDemo);
	return 0;
}

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



	//Character02_UI=========================
};
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

