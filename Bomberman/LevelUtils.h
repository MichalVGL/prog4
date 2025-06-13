#ifndef LEVELUTILS
#define LEVELUTILS

#include <string>
#include <vector>

#include "EnemyTypes.h"

namespace bm
{
	struct StageInfo
	{
		std::string name;
		std::vector<EnemyType> enemyTypes;
		int enemyCount;
		int wallCount;
		int powerUpCount;
	};

	enum class GameMode
	{
		singleplayer,
		coop,
		versus
	};

	struct LevelInfo
	{
		std::vector<StageInfo> stages;
		int playerLives;
		float levelTime;	//time in seconds for a stage
		GameMode gameMode;
		int savedScore{ 0 };	//score saved from the previous stage. (to reset to if the player fails)
	};
}

#endif // !LEVELUTILS
