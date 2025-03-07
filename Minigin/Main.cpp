#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//testing clone + additional tools

#include <memory>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "RenderComp.h"
#include "TransformComp.h"
#include "TextComp.h"
#include "FPSComp.h"
#include "RotationComp.h"
#include "IntCacheTestComp.h"
#include "GObjCacheTestComp.h"

void LoadDemo();
void LoadThrashTheCache();
 
int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(LoadThrashTheCache);
    return 0;
}

void LoadDemo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//dae::SceneManager::GetInstance().CreateScene("ImGui");
	//dae::SceneManager::GetInstance()

	//background=============================
	auto go = std::make_shared<dae::GameObject>();
	auto rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("background.tga");
	scene.Add(std::move(go));

	//dae logo===============================
	go = std::make_shared<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	rendComp->LoadTexture("logo.tga");
	auto tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(216, 180);
	scene.Add(std::move(go));

	//title==================================
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	go = std::make_shared<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(200, 20);
	auto textComp = go->AddComponent<TextComp>(font);
	textComp->SetText("Programming 4 Assignment");
	scene.Add(std::move(go));

	//fps counter============================
	go = std::make_shared<dae::GameObject>();
	rendComp = go->AddComponent<RenderComp>();
	tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(60, 20);
	textComp = go->AddComponent<TextComp>(font);
	textComp->SetText("00.00");
	go->AddComponent<FPSComp>(0.1f);
	//go->RemoveComponent<FPSComp>();	//tests for deletion
	//go->RemoveComponent<TransformComp>();
	scene.Add(std::move(go));


	//rotating characters====================
	//parent---------------
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition(100, 200);				//new way of setting local position, instead of tranComp = go->GetComponent<TransformComp>();
	scene.Add(go);																  //tranComp->SetLocalPosition(100, 200);
	//1st character--------
	auto go2 = std::make_shared<dae::GameObject>();
	go2->SetLocalPosition(30, 0);
	rendComp = go2->AddComponent<RenderComp>();
	rendComp->LoadTexture("playerIcon.png");
	go2->AddComponent<RotationComp>(-145.f);
	go2->SetParent(go.get(), false);
	//go2->SetParent(nullptr, true);	//unparent test
	scene.Add(go2);
	//2nd character--------
	auto go3 = std::make_shared<dae::GameObject>();
	go3->SetLocalPosition(0, 20);
	rendComp = go3->AddComponent<RenderComp>();
	rendComp->LoadTexture("playerIcon.png");
	go3->AddComponent<RotationComp>(360.f);
	go3->SetParent(go2.get(), false);
	scene.Add(go3);

	//removing GameObject test
	//scene.Remove(go2);	//removing GameObject that has a parent and child
}

void LoadThrashTheCache()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//title==================================
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComp>();
	auto tranComp = go->GetComponent<TransformComp>();
	tranComp->SetLocalPosition(20, 20);
	auto textComp = go->AddComponent<TextComp>(font);
	textComp->SetText("Prog4 Assignment: Thrash the Cache");
	scene.Add(std::move(go));

	//IntCacheTest===========================
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<IntCacheTestComp>();
	go->AddComponent<GObjCacheTestComp>();
	scene.Add(std::move(go));
}
