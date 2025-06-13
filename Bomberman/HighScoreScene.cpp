#include "HighScoreScene.h"

#include "ObjectConstructions.h"
#include "MenuScene.h"
#include "BMGameDefines.h"
#include "UIComponents.h"

bm::HighScoreScene::HighScoreScene()
{
}

void bm::HighScoreScene::Load()
{
	//title
	auto go = bm::TextGOBJ("HighScoreTitle");
	auto* textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText("High Score Achieved!!!");
	textComp->SetColor(s_YellowColor);
	auto* renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x / 2), static_cast<float>(WINDOW_BASESIZE.y) - 10 });
	Add(std::move(go));

	//score display
	auto& scoreSystem = BMServiceLocator::GetScoreSystem();

	go = bm::TextGOBJ("HighScoreTitle");
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText(std::format("SCORE: {:05}", scoreSystem.GetScore()));
	textComp->SetColor(s_YellowColor);
	renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x / 2), static_cast<float>(WINDOW_BASESIZE.y / 2) });
	Add(std::move(go));

	//input characters
	std::vector<std::pair<char, std::string>> inputElements{};
	inputElements.emplace_back('.', std::string{ '.' });	//empty char
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		inputElements.emplace_back(c, std::string{ c });
	}

	for (int i = 0; i < s_AmountOfChars; ++i)
	{
		go = bm::TextGOBJ(bm::IUI_GOBJID);
		textComp = go->GetComponent<dae::TextComp>();
		textComp->SetFont(bm::MAIN_FONT);
		textComp->SetSize(16);
		go->SetLocalPosition({ 20.f * (i + 1) + 20, static_cast<float>(WINDOW_BASESIZE.y * 1 / 3) });
		auto copy = inputElements;
		go->AddComponent<bm::SelectorUIComp<char>>(std::move(copy));
		m_HighScoreTextHandles.emplace_back(Add(std::move(go)));
	}

	//confirm
	go = bm::TextGOBJ(bm::IUI_GOBJID);
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetSize(16);
	textComp->SetText("Confirm");
	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x * 5 / 6), static_cast<float>(WINDOW_BASESIZE.y * 1 / 3) });

	go->AddComponent<bm::ExecutingUIComp>(std::make_unique<dae::FuncCommand>([this]() { ConfirmSelection(); }));	//add the command to start the game
	Add(std::move(go));

	//ExplorerObject=======================================================================
	go = bm::GOBJ("Explorer");
	go->AddComponent<bm::UIExplorerComp>(bm::UIExplorerComp::ExplorerMode::horizontal);
	Add(std::move(go));
}

void bm::HighScoreScene::Exit()
{
}

std::unique_ptr<dae::Scene> bm::HighScoreScene::UpdateScene(float)
{
	if (m_Confirmed == false)
		return nullptr;

	std::string name{};
	for (const auto& handle : m_HighScoreTextHandles)
	{
		if (!handle.Get())
			continue; //handle is invalid, skip it
		auto* inputComp = handle.Get()->GetComponent<bm::SelectorUIComp<char>>();
		if (inputComp)
		{
			name += inputComp->GetSelectedElement();
		}
	}

	if (name.empty())
	{
		return nullptr; //no name entered, do not add a high score
	}

	auto& scoreSystem = BMServiceLocator::GetScoreSystem();
	int finalScore = scoreSystem.GetScore();
	scoreSystem.AddHighScore(std::move(name));
	scoreSystem.ResetScore();

	return std::make_unique<bm::MenuScene>(finalScore);
}

void bm::HighScoreScene::ConfirmSelection()
{
	m_Confirmed = true;
}

//==========================================================
//==========================================================
//==========================================================
