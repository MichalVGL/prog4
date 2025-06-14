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
	inline constexpr glm::ivec2 WINDOW_BASESIZE{ 256, 240 };
	inline constexpr float RENDER_SCALE{ 2.f };
	inline constexpr float STAGE_TOTALTIME{ 200.f };

	//Tiles
	inline constexpr int TILE_SIZE{ 16 };
	inline constexpr int LEVELTILE_COLS{ 31 };	//31
	inline constexpr int LEVELTILE_ROWS{ 13 };	//13
	inline constexpr int LEVELTILES_TOTAL{ LEVELTILE_COLS * LEVELTILE_ROWS };

	//TileModID's
	inline constexpr TileModId WALL_MODID{"Wall"};
	inline constexpr TileModId DOOR_MODID{"Door"};
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
	inline constexpr glm::ivec2 PLAYER_START_TILE{ 1, 1 };
	inline constexpr dae::TextureEntry PLAYER_TEXTURE{ "Textures/Bomberman.png" };

	inline constexpr int ENEMYPLAYER_SCORE{ 1000 };

	//Enemies
	inline constexpr dae::GobjID ENEMY_GOBJID{ "Enemy" };
	inline constexpr int RANDOMPATH_MINTILES{ 4 };
	inline constexpr int RANDOMPATH_MAXTILES{ 12 };
	inline constexpr dae::TextureEntry ENEMY_TEXTURE{ "Textures/Enemies.png" };
	inline constexpr dae::TextureEntry ENEMYPLAYER_TEXTURE{ "Textures/PlayerEnemy.png" };

	//Various object names====================================================================
	inline constexpr dae::GobjID FIRE_GOBJID{ "Fire" };
	inline constexpr dae::GobjID BOMB_GOBJID{ "Bomb" };
	inline constexpr dae::GobjID UPGRADE_GOBJID{ "Upgrade" };
	inline constexpr dae::GobjID DOOR_GOBJID{ "Door" };

	//UI=============================================================================

	inline constexpr dae::GobjID IUI_GOBJID{ "InteractableUIElement" };

	//Other==========================================================================
	inline constexpr float GLOBAL_FPS{ 10 };
	inline constexpr float SOUNDVOLUME{ 0.1f };

	inline constexpr dae::FontEntry MAIN_FONT{ "Fonts/KenneyPixel.ttf" };

	inline constexpr dae::TextureEntry ERROR_TEXTURE{ "Textures/Error.png" };
}

#endif // !BMGAMEDEFINES_H
