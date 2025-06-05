#ifndef BMGAMEDEFINES_H
#define BMGAMEDEFINES_H

#include <TextureEntry.h>
#include <SpriteComp.h>
#include <GameObject.h>

#include "EntityUtils.h"
#include "TileMod.h"

namespace bm
{
	//general level vars=============================================================

	//Tiles
	inline constexpr int TILE_SIZE{ 16 };
	inline constexpr int LEVELTILE_COLS{ 31 };	//31
	inline constexpr int LEVELTILE_ROWS{ 13 };	//13
	inline constexpr int LEVELTILES_TOTAL{ LEVELTILE_COLS * LEVELTILE_ROWS };

	//TileModID's
	inline constexpr TileModId WALL_MODID{"Wall"};

	//Entity vars====================================================================

	//General Entity Stats
	inline constexpr EntityStats ENTITYSTATS_SLOW{ .movementSpeed = 25.f };
	inline constexpr EntityStats ENTITYSTATS_MEDIUM{ .movementSpeed = 35.f };
	inline constexpr EntityStats ENTITYSTATS_FAST{ .movementSpeed = 40.f };

	//State Sprite IDs
	inline constexpr int IDLEFRAME{ 1 };
	inline constexpr dae::sprite_id SPRITEID_MOVEUP{ dae::SpriteId("MoveUp") };
	inline constexpr dae::sprite_id SPRITEID_MOVELEFT{ dae::SpriteId("MoveLeft") };
	inline constexpr dae::sprite_id SPRITEID_MOVEDOWN{ dae::SpriteId("MoveDown") };
	inline constexpr dae::sprite_id SPRITEID_DEATH{ dae::SpriteId("Death") };

	//Player
	inline constexpr dae::GobjID PLAYER_GOBJID{ "Bomberman" };
	inline constexpr int PLAYER_START_LIVES{ 3 };
	inline constexpr dae::TextureEntry PLAYER_TEXTUREENTRY{ "Bomberman.png" };

	//Enemies
	inline constexpr dae::GobjID ENEMY_GOBJID{ "Enemy" };
	inline constexpr int RANDOMPATH_MINTILES{ 4 };
	inline constexpr int RANDOMPATH_MAXTILES{ 10 };
	inline constexpr dae::TextureEntry ENEMY_TEXTUREENTRY{ "Enemies.png" };


	//Other==========================================================================
	inline constexpr float GLOBAL_FPS{ 8 };

	inline constexpr dae::TextureEntry ERROR_TEXTURE{ "Error.png" };

}

#endif // !BMGAMEDEFINES_H
