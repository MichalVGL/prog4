#ifndef BMGAMEDEFINES_H
#define BMGAMEDEFINES_H

#include <TextureEntry.h>
#include <SpriteComp.h>

namespace bm
{
	//general level vars=============================================================

	//Tiles
	inline constexpr int TILE_SIZE{ 16 };
	inline constexpr int LEVELTILE_COLS{ 31 };	//31
	inline constexpr int LEVELTILE_ROWS{ 13 };	//13
	inline constexpr int LEVELTILES_TOTAL{ LEVELTILE_COLS * LEVELTILE_ROWS };

	//Entity vars====================================================================

	//Sprites
	inline constexpr int IDLEFRAME{ 1 };
	inline constexpr dae::sprite_id SPRITEID_MOVEUP{dae::SpriteId("MoveUp")};
	inline constexpr dae::sprite_id SPRITEID_MOVERIGHT{dae::SpriteId("MoveRight")};
	inline constexpr dae::sprite_id SPRITEID_MOVEDOWN{dae::SpriteId("MoveDown")};
	//inline constexpr dae::sprite_id SPRITEID_MOVELEFT{dae::SpriteId("MoveLeft")};	//reversed right
	inline constexpr dae::sprite_id SPRITEID_DEATH{dae::SpriteId("Death")};

	//Player
	inline constexpr int PLAYER_START_LIVES{ 3 };

	//Other==========================================================================
	inline constexpr dae::TextureEntry ERROR_TEXTURE{ "Error.png" };

}

#endif // !BMGAMEDEFINES_H
