#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

namespace bm
{
	enum class EnemyType
	{
		balloom,
		oneal,
		doll,
		minvo
		//player
	};

	inline constexpr int BALLOOM_SCORE{ 100 };
	inline constexpr int ONEAL_SCORE{ 200 };
	inline constexpr int DOLL_SCORE{ 300 };
	inline constexpr int MINVO_SCORE{ 400 };
}

#endif // !ENEMYTYPES_H
