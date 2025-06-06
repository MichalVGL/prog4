#include "FireComp.h"

#include "BMServiceLocator.h"
#include "BMGameDefines.h"
#include "BombComp.h"
#include "WallComp.h"
#include "ObjectFinder.h"

bm::FireComp::FireComp(dae::GameObject& parent, std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount)
	:Component(parent)
{
	if(targets.empty())
		targets = bm::FindObjects({ bm::PLAYER_GOBJID, bm::ENEMY_GOBJID });

	m_SpriteComp.Init(GetOwner());
	m_SpriteComp->LoadTexture(s_FireTexture);
	m_SpriteComp->SetFPS(GLOBAL_FPS);
	m_SpriteComp->SetAlignment(dae::HorizontalAlignment::center, dae::VerticalAlignment::center);

	//todo, setup collision with targets

	float totalRotation = [&]() -> float
		{
			switch (direction)
			{
			case bm::Direction::down:
				return 180.f;
			case bm::Direction::left:
				return 270.f;
			case bm::Direction::right:
				return 90.f;
			default:
				return 0.f;
			}
		}();
	switch (direction)
	{
	case bm::Direction::left:
	case bm::Direction::down:
	case bm::Direction::right:
	case bm::Direction::up:	//direction based

		m_SpriteComp->SetRotation(totalRotation);

		if (spreadAmount > 0)
		{
			m_SpriteComp->AddSpriteEntry(s_ConnectedSprite);
			m_SpriteComp->SetSpriteEntry(s_ConnectedSprite.id);
			HandleAllAdjacentTiles(targets, spreadAmount);
		}
		else
		{
			m_SpriteComp->AddSpriteEntry(s_EndSprite);
			m_SpriteComp->SetSpriteEntry(s_EndSprite.id);
		}

		break;
	case bm::Direction::all:

		m_SpriteComp->AddSpriteEntry(s_OmniSprite);
		m_SpriteComp->SetSpriteEntry(s_OmniSprite.id);

		if(spreadAmount > 0)
			HandleAllAdjacentTiles(targets, spreadAmount);
		break;
	}
}

void bm::FireComp::Update(float)
{
	if (m_SpriteComp->IsLoopComplete())
	{
		GetOwner().FlagForDeletion();
	}
}

void bm::FireComp::HandleNextTile(std::vector<dae::GameObjectHandle> targets, Direction direction, int spreadAmount)
{
	bm::TileComp* nextTile = [&]() -> bm::TileComp*
		{
			auto& tileSystem = bm::BMServiceLocator::GetTileSystem();
			auto* currentTile = tileSystem.GetTileFromWorldPos(GetOwner().GetWorldPos());
			if (!currentTile)
				return nullptr;

			switch (direction)
			{
			case bm::Direction::up:
				return currentTile->GetUpTile();
			case bm::Direction::down:
				return currentTile->GetDownTile();
			case bm::Direction::left:
				return currentTile->GetLeftTile();
			case bm::Direction::right:
				return currentTile->GetRightTile();
			}

			return nullptr;
		}();

	//
	if (!nextTile)
		return;

	if (TileMod* tileMod = nextTile->GetTileMod(); tileMod != nullptr)
	{
		if (tileMod->GetId() == BOMB_MODID)
		{
			BombComp* bombComp = static_cast<BombComp*>(tileMod);
			bombComp->Detonate();
		}
		else if (tileMod->GetId() == WALL_MODID)
		{
			WallComp* wallComp = static_cast<WallComp*>(tileMod);
			wallComp->DestroyWall();
		}
		return;	// prevent spawn with a tilemod
	}

	if (!nextTile->IsWalkable())
		return;	//prevent spawn on a non-walkable tile

	//only spawn fire if the tile is walkable and doesnt have a TileMod.
	auto& spawnSystem = bm::BMServiceLocator::GetSpawnSystem();
	spawnSystem.SpawnFire(nextTile->GetPosition(), targets, direction, spreadAmount - 1);
}

void bm::FireComp::HandleAllAdjacentTiles(std::vector<dae::GameObjectHandle> targets, int spreadAmount)
{
	HandleNextTile(targets, Direction::up, spreadAmount);
	HandleNextTile(targets, Direction::down, spreadAmount);
	HandleNextTile(targets, Direction::left, spreadAmount);
	HandleNextTile(targets, Direction::right, spreadAmount);
}
