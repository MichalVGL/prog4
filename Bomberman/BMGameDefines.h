#ifndef BMGAMEDEFINES_H
#define BMGAMEDEFINES_H

#include <TextureEntry.h>

namespace bm
{
	//general level vars
	inline constexpr int TILE_SIZE{ 16 };
	inline constexpr int LEVELTILE_COLS{ 31 };	//31
	inline constexpr int LEVELTILE_ROWS{ 13 };	//13
	inline constexpr int LEVELTILES_TOTAL{ LEVELTILE_COLS * LEVELTILE_ROWS };


	//player vars
	inline constexpr int PLAYER_START_LIVES{ 3 };

	//
	inline constexpr dae::TextureEntry ERROR_TEXTURE{ "Error.png" };

}

#endif // !BMGAMEDEFINES_H
