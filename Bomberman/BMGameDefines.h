#ifndef BMGAMEDEFINES_H
#define BMGAMEDEFINES_H

#include <Texture.h>
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
	inline constexpr TileModId BOMB_MODID{"Bomb"};
	inline constexpr TileModId UPGRADE_MODID{"Upgrade"};

	//Entity vars====================================================================

	//General Entity Stats
	inline constexpr EntityStats ENTITYSTATS_SLOW{ .movementSpeed = 30.f };
	inline constexpr EntityStats ENTITYSTATS_MEDIUM{ .movementSpeed = 40.f };
	inline constexpr EntityStats ENTITYSTATS_FAST{ .movementSpeed = 50.f };

	//State Sprite IDs
	inline constexpr int IDLEFRAME{ 1 };
	inline constexpr dae::sprite_id SPRITEID_MOVEUP{ dae::SpriteId("MoveUp") };
	inline constexpr dae::sprite_id SPRITEID_MOVELEFT{ dae::SpriteId("MoveLeft") };
	inline constexpr dae::sprite_id SPRITEID_MOVEDOWN{ dae::SpriteId("MoveDown") };
	inline constexpr dae::sprite_id SPRITEID_DEATH{ dae::SpriteId("Death") };

	//Player
	inline constexpr dae::GobjID PLAYER_GOBJID{ "Bomberman" };
	inline constexpr int PLAYER_START_LIVES{ 3 };
	inline constexpr dae::TextureEntry PLAYER_TEXTURE{ "Bomberman.png" };

	//Enemies
	inline constexpr dae::GobjID ENEMY_GOBJID{ "Enemy" };
	inline constexpr int RANDOMPATH_MINTILES{ 4 };
	inline constexpr int RANDOMPATH_MAXTILES{ 10 };
	inline constexpr dae::TextureEntry ENEMY_TEXTURE{ "Enemies.png" };

	//Various object names====================================================================
	inline constexpr dae::GobjID FIRE_GOBJID{ "Fire" };
	inline constexpr dae::GobjID BOMB_GOBJID{ "Bomb" };
	inline constexpr dae::GobjID UPGRADE_GOBJID{ "Upgrade" };

	//Other==========================================================================
	inline constexpr float GLOBAL_FPS{ 10 };
	inline constexpr float SOUNDVOLUME{ 0.1f };

	inline constexpr dae::FontEntry MAIN_FONT{ "Fonts/KenneyPixel.ttf" };

	inline constexpr dae::TextureEntry ERROR_TEXTURE{ "Error.png" };
}

#endif // !BMGAMEDEFINES_H
