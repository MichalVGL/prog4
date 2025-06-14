#include "LevelScene.h"

#include <SDL.h>

#include "StartStageScene.h"
#include "BMServiceLocator.h"
#include "TileSystem.h"
#include "EnemyTypes.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "LevelSoundsPlayer.h"

#include "MenuScene.h"
#include "HighScoreScene.h"

bm::LevelScene::LevelScene(LevelInfo&& lvlInfo)
	:m_LevelInfo{ std::move(lvlInfo) }
{
	if (m_LevelInfo.stages.size() == 0)
	{
		std::cout << std::format("Error: LevelInfo has no stages!\n");
		throw std::invalid_argument("LevelInfo has no stages");
	}
	m_CurrentStageInfo = m_LevelInfo.stages.back();	//will be popped is the level is succesfull
}

void bm::LevelScene::Load()
{
	//setup systems======================================================================
	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	renderSystem.SetBackgroundColor({ .r = 156, .g = 156, .b = 156, .a = 255 });

	auto& cameraSystem = dae::ServiceLocator::GetCameraSystem();
	cameraSystem.SetBounds({ 0, 0, 496, 240 });

	bm::BMServiceLocator::RegisterTileSystem(std::make_unique<bm::Level_TileSystem>());
	auto& tileSystem = BMServiceLocator::GetTileSystem();

	bm::BMServiceLocator::RegisterLevelSoundsPlayer(std::make_unique<bm::Default_LevelSoundsPlayer>());

	auto& spawnSystem = BMServiceLocator::GetSpawnSystem();

	//setup the tiles====================================================================
	auto* playerTile = tileSystem.GetTileFromIndex(bm::PLAYER_START_TILE);
	std::vector<bm::TileComp*> playerSpawnTiles{};	//spawn itself and the tiles
	if (playerTile)
	{
		playerSpawnTiles.push_back(playerTile);
		if (playerTile->GetUpTile())
			playerSpawnTiles.push_back(playerTile->GetUpTile());
		if (playerTile->GetRightTile())
			playerSpawnTiles.push_back(playerTile->GetRightTile());
		if (playerTile->GetDownTile())
			playerSpawnTiles.push_back(playerTile->GetDownTile());
		if (playerTile->GetLeftTile())
			playerSpawnTiles.push_back(playerTile->GetLeftTile());
	}
	else
	{
		std::cout << std::format("Error: Player start tile ({}, {}) not found!\n", bm::PLAYER_START_TILE.x, bm::PLAYER_START_TILE.y);
		return;
	}

	spawnSystem.SpawnLevelWalls(m_CurrentStageInfo.wallCount, m_CurrentStageInfo.powerUpCount, playerSpawnTiles);
	SpawnSafetyWalls(playerSpawnTiles);

	//spawn enemies======================================================================
	spawnSystem.SpawnEnemies(m_CurrentStageInfo.enemyCount, m_CurrentStageInfo.enemyTypes, playerSpawnTiles);

	//spawn player(s)====================
	spawnSystem.SpawnPlayer(m_LevelInfo.gameMode, false);
	if (m_LevelInfo.gameMode == bm::GameMode::coop)
	{
		spawnSystem.SpawnPlayer(m_LevelInfo.gameMode, true);
	}
	else if (m_LevelInfo.gameMode == bm::GameMode::versus)
	{
		spawnSystem.SpawnPlayerEnemy(m_LevelInfo.gameMode, true);
	}

	//setup ui===========================
	SetupUI();

	//play soundtrack===================
	m_SoundtrackToken.Play(1, -1);

	//setup player handles==============
	m_PlayerHandles = GetObjectsByID(bm::PLAYER_GOBJID);

	//setup mute functionality (extension, sound volume is set in bomberman.cpp)
	auto& inputManager = dae::InputManager::GetInstance();
	m_RestartSoundtrackBinding = std::make_unique<dae::KeyboardBinding>(inputManager.CreateBinding(SDL_SCANCODE_F2, dae::KeyState::down,
		std::make_unique<RestartSoundtrackCommand>(*this)));
	inputManager.RegisterBinding(m_RestartSoundtrackBinding.get());

	//setup f1 skip cheat
	m_SkipLevelBinding = std::make_unique<dae::KeyboardBinding>(inputManager.CreateBinding(SDL_SCANCODE_F1, dae::KeyState::down,
		std::make_unique<SkipLevelCommand>(*this)));
	inputManager.RegisterBinding(m_SkipLevelBinding.get());
}

void bm::LevelScene::Exit()
{
	bm::BMServiceLocator::RegisterTileSystem(std::make_unique<bm::Null_TileSystem>());
	bm::BMServiceLocator::RegisterLevelSoundsPlayer(std::make_unique<bm::Null_LevelSoundsPlayer>());
	dae::ServiceLocator::GetCameraSystem().Reset();

	auto& renderSystem = dae::ServiceLocator::GetRenderSystem();
	renderSystem.SetBackgroundColor({ .r = 0, .g = 0, .b = 0, .a = 255 });

	auto& inputManager = dae::InputManager::GetInstance();
	if (m_RestartSoundtrackBinding)
	{
		inputManager.UnRegisterBinding(m_RestartSoundtrackBinding.get());
	}
	if (m_SkipLevelBinding)
	{
		inputManager.UnRegisterBinding(m_SkipLevelBinding.get());
	}
}

std::unique_ptr<dae::Scene> bm::LevelScene::UpdateScene(float)
{
	BMServiceLocator::GetLevelSoundsPlayer().Update();

	if (m_PlayerEscaped)	//succes
	{
		m_LevelInfo.stages.pop_back();

		auto& scoreSystem = BMServiceLocator::GetScoreSystem();
		if (m_LevelInfo.stages.empty())	//all stages complete
		{
			auto& upgradeSystem = BMServiceLocator::GetUpgradeSystem();
			upgradeSystem.ResetUpgrades();
			if (scoreSystem.IsHighScore() && m_LevelInfo.gameMode == GameMode::singleplayer)	//high score (only in singlelayer)
			{
				return std::make_unique<bm::HighScoreScene>();
			}
			else
			{
				int finalScore = scoreSystem.GetScore();
				scoreSystem.ResetScore();
				return std::make_unique<bm::MenuScene>(finalScore);
			}
		}
		else //next stage
		{
			m_LevelInfo.savedScore = scoreSystem.GetScore();
			return std::make_unique<StartStageScene>(std::make_unique<bm::LevelScene>(std::move(m_LevelInfo)));
		}
	}


	UpdateHandles(m_PlayerHandles);
	if (m_PlayerHandles.size() == 0 || m_TimerFinished) //player failed
	{
		m_LevelInfo.playerLives--;
		if (m_LevelInfo.playerLives < 0)
		{
			auto& upgradeSystem = BMServiceLocator::GetUpgradeSystem();	//only reset upgrades when game is over, failing doesnt reset the upgrades
			upgradeSystem.ResetUpgrades();
			return std::make_unique<bm::MenuScene>();
		}
		auto& scoreSystem = BMServiceLocator::GetScoreSystem();
		scoreSystem.SetScore(m_LevelInfo.savedScore);

		return std::make_unique<StartStageScene>(std::make_unique<bm::LevelScene>(std::move(m_LevelInfo)));
	}

	return nullptr;
}

//=====================================================================================

const bm::LevelInfo& bm::LevelScene::GetLevelInfo() const
{
	return m_LevelInfo;
}

//=====================================================================================
//=====================================================================================
//=====================================================================================

void bm::LevelScene::RestartSoundtrack()
{
	m_SoundtrackToken.Stop();
	m_SoundtrackToken.Play(1, -1);
}

void bm::LevelScene::OnObjectAdded(dae::GameObjectHandle object)
{
	//setup door when the door is spawned
	if (object && object->GetId() == DOOR_GOBJID)
	{
		auto* doorComp = object->GetComponent<bm::DoorComp>();
		doorComp->OnPlayerEscaped().AddObserver(this);
	}
}

void bm::LevelScene::SetupUI()
{
	auto go = bm::GOBJ("UIParent");
	go->AddComponent<dae::FollowCameraComp>();
	auto uiParent = Add(std::move(go));

	float margin{ 5.f };

	//Timer================
	go = bm::TextGOBJ("LevelTimer");
	auto* textComp = go->GetComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(bm::MAIN_FONT);
	auto* timerComp = go->AddComponent<bm::TimerComp>(s_LevelTime, true);
	timerComp->OnTimerComplete().AddObserver(this);
	timerComp->SetFormatFunction([](float time) -> std::string
		{
			return std::format("TIME {:.0f}", time);
		});
	auto* renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::left);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);

	go->SetLocalPosition({ margin, static_cast<float>(WINDOW_BASESIZE.y) - margin });
	go->SetParent(uiParent, true);

	m_TimerHandle = Add(std::move(go));

	//Lives================
	go = bm::TextGOBJ("Lives");
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetText(std::format("LEFT {}", m_LevelInfo.playerLives));

	renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::right);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);

	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x) - margin, static_cast<float>(WINDOW_BASESIZE.y) - margin });
	go->SetParent(uiParent, true);

	Add(std::move(go));

	//Score================
	go = bm::TextGOBJ("Score");
	textComp = go->GetComponent<dae::TextComp>();
	textComp->SetSize(16);
	textComp->SetFont(bm::MAIN_FONT);
	textComp->SetTextFunc([]() -> std::string
		{
			auto& scoreSystem = BMServiceLocator::GetScoreSystem();
			return std::format("{:05}", scoreSystem.GetScore());
		});

	renderComp = go->GetComponent<dae::RenderComp>();
	renderComp->SetHorizontalAlignment(dae::HorizontalAlignment::left);
	renderComp->SetVerticalAlignment(dae::VerticalAlignment::top);

	go->SetLocalPosition({ static_cast<float>(WINDOW_BASESIZE.x / 2) , static_cast<float>(WINDOW_BASESIZE.y) - margin });
	go->SetParent(uiParent, true);

	Add(std::move(go));
}

void bm::LevelScene::SpawnSafetyWalls(std::vector<bm::TileComp*> playerTiles)
{
	if (playerTiles.empty()) return;

	auto& spawnSystem = BMServiceLocator::GetSpawnSystem();

	// Start from index 1 to skip the first tile (playertile)
	for (size_t i = 1; i < playerTiles.size(); ++i)
	{
		auto* tile = playerTiles[i];
		if (!tile) continue;

		std::array<bm::TileComp*, 4> neighbors = {
			tile->GetUpTile(),
			tile->GetRightTile(),
			tile->GetDownTile(),
			tile->GetLeftTile()
		};

		// Remove playerTiles[1] if present in neighbors
		auto* skipTile = playerTiles[0];
		for (auto& neighbor : neighbors)
		{
			if (neighbor == skipTile)
				neighbor = nullptr;
		}

		//spawn a wall if free
		for (auto* neighbor : neighbors)
		{
			if (neighbor && neighbor->IsWalkable() && !neighbor->HasTileMod())
			{
				spawnSystem.SpawnWall(neighbor->GetPosition(), bm::ContainedObject::none);
			}
		}
	}
}

void bm::LevelScene::Notify(dae::Event event, const std::any&)
{
	if (event == TimerComp::s_TimerCompleteEvent)
	{
		m_TimerFinished = true;
	}
	else if (event == DoorComp::s_PlayerEscaped)
	{
		m_PlayerEscaped = true;
	}
}

//==============================

bm::SkipLevelCommand::SkipLevelCommand(LevelScene& levelScene)
	:m_Level{ levelScene }
{
}

void bm::SkipLevelCommand::Execute()
{
	m_Level.m_PlayerEscaped = true;	//force the level to be skipped
}
