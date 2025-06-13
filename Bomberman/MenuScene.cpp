#include "MenuScene.h"

#include "UIComponents.h"

#include "BMGameDefines.h"
#include "ObjectConstructions.h"
#include "LevelUtils.h"

#include "StartStageScene.h"
#include "LevelScene.h"

bm::MenuScene::MenuScene(int achievedScore)
	:m_AchievedScore{ achievedScore }
	, m_HighScores{ BMServiceLocator::GetScoreSystem().GetHighScores() }
{
}

void bm::MenuScene::Load()
{
	//setup the menu UI===================================================================
	auto go = bm::RenderGOBJ("MenuTitle");
	auto* renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);
	renderComp->LoadImageTexture(s_MenuTitle);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x / 2), static_cast<float>(WINDOW_BASESIZE.y) - 10 });
	Add(std::move(go));

	//Last score==========================================================================
	go = bm::TextGOBJ("LastScore");
	auto* textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(8);
	textComp->SetText("last score: " + std::to_string(m_AchievedScore));
	textComp->SetColor(s_YellowColor);
	renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 1 / 4), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3 + 10) });
	Add(std::move(go));

	//Highscores==========================================================================
	go = bm::TextGOBJ("HighScores");
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText("HighScores");
	textComp->SetColor(s_YellowColor);
	renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 3 / 4), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3 + 10) });
	Add(std::move(go));

	//Highscores list
	for (size_t i{ 0 }; i < m_HighScores.size(); ++i)
	{
		auto& highScore = m_HighScores[i];

		go = bm::TextGOBJ("HighScore");
		textComp = go->GetComponent<dae::TextComp>();
		textComp->SetFont(bm::MAIN_FONT);
		textComp->SetSize(8);
		textComp->SetText(std::format("{:05} - {}", highScore.score, highScore.name));
		textComp->SetColor(s_PurpleColor);
		renderComp = go->GetComponent<dae::RenderComp>();
		renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::left);
		renderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
		go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 2 / 4 + 20), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3 - 10 - (i * 10)) });
		Add(std::move(go));
	}

	//UI==================================================================================
	//Start
	go = bm::TextGOBJ(bm::IUI_GOBJID);
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText("Start");

	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 1 / 4), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3 - 15) });

	go->AddComponent<bm::ExecutingUIComp>(std::make_unique<dae::FuncCommand>([this]() { StartGame(); }));	//add the command to start the game
	Add(std::move(go));

	//GameMode
	go = bm::TextGOBJ(bm::IUI_GOBJID);
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);

	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 1 / 4), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3 - 40) });

	std::vector<std::pair<bm::GameMode, std::string>> gameModeElements{};
	gameModeElements.emplace_back(bm::GameMode::singleplayer, "Solo");
	gameModeElements.emplace_back(bm::GameMode::coop, "Co-op");
	gameModeElements.emplace_back(bm::GameMode::versus, "Versus");
	go->AddComponent<bm::SelectorUIComp<bm::GameMode>>(std::move(gameModeElements));
	m_ModeUIElementHandle = Add(std::move(go));

	//ExplorerObject=======================================================================
	//used to interact with the UI
	go = bm::GOBJ("Explorer");
	go->AddComponent<bm::UIExplorerComp>(bm::UIExplorerComp::ExplorerMode::vertical);
	Add(std::move(go));
}

void bm::MenuScene::Exit()
{
}

std::unique_ptr<dae::Scene> bm::MenuScene::UpdateScene(float)
{
	if (!m_StartCalled)
		return nullptr;

	if (m_ModeUIElementHandle.Get() == nullptr)
	{
		std::cout << "Error: Mode UI Element handle is null [MenuScene]\n";
		throw std::runtime_error("Mode UI Element handle is null [MenuScene]");
	}

	auto* modeUIComp = m_ModeUIElementHandle.Get()->GetComponent<bm::SelectorUIComp<bm::GameMode>>();

	bm::StageInfo stageOne{ .name = "1", .enemyTypes = { bm::EnemyType::balloom }, .enemyCount = 8, .wallCount = 70, .powerUpCount = 2 };
	bm::StageInfo stageTwo{ .name = "2", .enemyTypes = { bm::EnemyType::oneal }, .enemyCount = 8, .wallCount = 70, .powerUpCount = 2 };
	bm::StageInfo stageThree{ .name = "3", .enemyTypes = { bm::EnemyType::doll, bm::EnemyType::minvo }, .enemyCount = 8, .wallCount = 70, .powerUpCount = 2 };

	if (modeUIComp->GetSelectedElement() == bm::GameMode::versus)
	{
		stageOne.enemyCount = 4; //reduce ai enemy count for versus mode
		stageTwo.enemyCount = 4;
		stageThree.enemyCount = 4;

		stageOne.wallCount = 40; //reduce wall count for versus mode
		stageTwo.wallCount = 40;
		stageThree.wallCount = 40;
	}

	bm::LevelInfo levelInfo{ .stages = { stageThree, stageTwo, stageOne }, .playerLives = bm::PLAYER_START_LIVES, .levelTime = bm::STAGE_TOTALTIME, .gameMode = modeUIComp->GetSelectedElement()};

	return std::make_unique<bm::StartStageScene>(std::move(std::make_unique<bm::LevelScene>(std::move(levelInfo))));
}

//=====================================================================
//=====================================================================
//=====================================================================

void bm::MenuScene::StartGame()
{
	m_StartCalled = true;
}