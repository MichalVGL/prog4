#include "StartStageScene.h"

#include "BMGameDefines.h"
//#include "BMServiceLocator.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "LevelScene.h" 

bm::StartStageScene::StartStageScene(std::unique_ptr<dae::Scene>&& scene)
	:m_LevelScene{ std::move(scene) }
{
	m_SoundtrackToken.Play();
}

void bm::StartStageScene::Load()
{
	LevelScene* pLevelScene = dynamic_cast<LevelScene*>(m_LevelScene.get());
	if (!pLevelScene)
	{
		std::cout << std::format("Error: StartStageScene must receive a LevelScene\n");
		throw std::invalid_argument("Invalid scene type passed to StartStageScene");
	}

	//center text
	auto go = TextGOBJ("Text");
	auto* textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText("STAGE " + pLevelScene->GetLevelInfo().stages.back().name);
	auto* renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x / 2), static_cast<float>(WINDOW_BASESIZE.y / 2) });
	Add(std::move(go));
}

void bm::StartStageScene::Exit()
{
}

std::unique_ptr<dae::Scene> bm::StartStageScene::UpdateScene(float deltaTime)
{
	m_RemainingTime -= deltaTime;
	if (m_RemainingTime <= 0.f)
	{
		return std::move(m_LevelScene);
	}

	return nullptr;
}
