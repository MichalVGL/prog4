#if false	//only for transfer to gameproject, TODO delete

/*
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//testing clone + additional tools

#include <memory>
#include <Windows.h>
#include <Xinput.h>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"

#include "TextComp.h"
#include "FPSComp.h"
#include "RotationComp.h"
#include "GameActorComp.h"
#include "HealthComp.h"
#include "UIHealthComp.h"
#include "ScoreComp.h"
#include "UIScoreComp.h"

#include "GameActorCommands.h"

void LoadDemo();
void LoadThrashTheCache();
void LoadInputDemo();

 
int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(LoadInputDemo);
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

	//dae logo===============================
	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("logo.tga");
	auto tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(216, 180);
	scene.Add(std::move(go));

	//title==================================
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(200, 20);
	auto textComp = go->AddComponent<TextComp>(font);
	textComp->SetText("Programming 4 Assignment");
	scene.Add(std::move(go));

	//fps counter============================
	go = std::make_unique<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(60, 20);
	textComp = go->AddComponent<TextComp>(font);
	//textComp = go->AddComponent<TextComp>();
	textComp->SetText("00.00");
	go->AddComponent<FPSComp>(0.1f);
	//go->RemoveComponent<FPSComp>();	//tests for deletion
	//go->RemoveComponent<TransformComp>();
	scene.Add(std::move(go));


	//rotating characters====================
	//parent---------------
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition(100, 200);				//new way of setting local position, instead of tranComp = go->GetComponent<TransformComp>();
	auto* pGameObject = scene.Add(std::move(go));																  //tranComp->SetLocalPosition(100, 200);
	//1st character--------
	auto go2 = std::make_unique<dae::GameObject>();
	go2->SetLocalPosition(30, 0);
	rendComp = go2->AddComponent<RenderComp>();
	rendComp->LoadTexture("playerIcon.png");
	go2->AddComponent<RotationComp>(-145.f);
	go2->SetParent(pGameObject, false);
	//go2->SetParent(nullptr, true);	//unparent test
	pGameObject = scene.Add(std::move(go2));
	//2nd character--------
	auto go3 = std::make_unique<dae::GameObject>();
	go3->SetLocalPosition(0, 20);
	rendComp = go3->AddComponent<RenderComp>();
	rendComp->LoadTexture("playerIcon.png");
	go3->AddComponent<RotationComp>(360.f);
	go3->SetParent(pGameObject, false);
	scene.Add(std::move(go3));

	//removing GameObject test
	scene.Remove(pGameObject);	//removing GameObject that has a parent and child
}

void LoadThrashTheCache()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//title==================================
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComp>();
	auto tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 20);
	auto textComp = go->AddComponent<TextComp>(font);
	textComp->SetText("Prog4 Assignment: Thrash the Cache");
	scene.Add(std::move(go));

	//IntCacheTest===========================
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<IntCacheTestComp>();
	go->AddComponent<GObjCacheTestComp>();
	scene.Add(std::move(go));
}

void LoadInputDemo()
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
}
*/
#endif // false
