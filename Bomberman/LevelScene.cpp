#include "LevelScene.h"

#include <SDL.h>

#include "BMServiceLocator.h"
#include "TileSystem.h"
#include "EnemyTypes.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "LevelSoundsPlayer.h"

bm::LevelScene::LevelScene(int lives)
	:m_PlayerLives{ lives }
{

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

	spawnSystem.SpawnLevelWalls(2, 1, playerSpawnTiles);
	SpawnSafetyWalls(playerSpawnTiles);

	//spawn enemies======================================================================
	spawnSystem.SpawnEnemies(1, { bm::EnemyType::balloom, bm::EnemyType::oneal }, playerSpawnTiles);

	//spawn player(s)====================
	spawnSystem.SpawnPlayer();

	//setup ui===========================
	SetupUI();

	//play soundtrack===================
	m_SoundtrackToken.Play(1, -1);

	//setup player handles==============
	m_PlayerHandles = GetObjectsByID(bm::PLAYER_GOBJID);

	//setup mute functionality (extension, sound is set in bomberman.cpp)
	auto& inputManager = dae::InputManager::GetInstance();
	m_RestartSoundtrackBinding = std::make_unique<dae::KeyboardBinding>(inputManager.CreateBinding(SDL_SCANCODE_F2, dae::KeyState::down,
		std::make_unique<RestartSoundtrackCommand>(*this)));
	inputManager.RegisterBinding(m_RestartSoundtrackBinding.get());
}

void bm::LevelScene::Exit()
{
	bm::BMServiceLocator::RegisterTileSystem(std::make_unique<bm::Null_TileSystem>());
	bm::BMServiceLocator::RegisterLevelSoundsPlayer(std::make_unique<bm::Null_LevelSoundsPlayer>());
}

std::unique_ptr<dae::Scene> bm::LevelScene::UpdateScene(float deltaTime)
{
	BMServiceLocator::GetLevelSoundsPlayer().Update();
	
	//succes
	if (m_PlayerEscaped)
	{
		return std::make_unique<bm::LevelScene>(m_PlayerLives);
	}

	//player died
	UpdateHandles(m_PlayerHandles);
	if (m_PlayerHandles.size() == 0)
	{
		//failed, got killed
		return std::make_unique<bm::LevelScene>(m_PlayerLives);
	}

	//time ran out
	if (m_TimerFinished)
	{
		return std::make_unique<bm::LevelScene>(m_PlayerLives);
	}

	deltaTime;
	return nullptr;
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
	textComp->SetText(std::format("LEFT {}", m_PlayerLives));

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

