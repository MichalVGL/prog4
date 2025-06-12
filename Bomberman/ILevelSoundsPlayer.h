#ifndef ILEVELSOUNDSPLAYER_H
#define ILEVELSOUNDSPLAYER_H

namespace bm
{
	enum class LevelSound
	{
		explosion,
		bombDeployed,
		powerUp
	};

	//this class is used to play sounds that are common in the game. 
	//to prevent sounds overlapping and/or being destroyed because the gameobject is deleted
	//not all sounds are played through this
	class ILevelSoundsPlayer
	{
	public: 

		virtual ~ILevelSoundsPlayer() = default;

		virtual void PlaySound(LevelSound sound) = 0;

		virtual void Update() = 0;	//to be called from the level script

	};
}

#endif // !ILEVELSOUNDSPLAYER_H
