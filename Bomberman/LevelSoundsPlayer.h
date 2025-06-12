#ifndef LEVELSOUNDSPLAYER_H
#define LEVELSOUNDSPLAYER_H

#include "ILevelSoundsPlayer.h"
#include <unordered_set>
#include <Sound.h>

namespace bm
{
	class Null_LevelSoundsPlayer final : public ILevelSoundsPlayer
	{
	public:

		// Inherited via ILevelSoundsPlayer
		void PlaySound(LevelSound) override {};
		void Update() override {};
	};

	class Default_LevelSoundsPlayer final : public ILevelSoundsPlayer
	{
	public:

		// Inherited via ILevelSoundsPlayer
		void PlaySound(LevelSound sound) override;
		void Update() override;

	private:

		void PlaySoundToken(dae::SoundToken& token);

		std::unordered_set<LevelSound> m_RequestedSounds;

		//tokens 
		dae::SoundToken m_ExplosionSoundToken{ s_ExplosionSoundEntry };
		dae::SoundToken m_BombDeployedSoundToken{ s_BombDeployedSoundEntry };
		dae::SoundToken m_PowerUpSoundToken{ s_PowerUpSoundEntry };

		//entries
		static constexpr dae::SoundEntry s_ExplosionSoundEntry{ "Sounds/Explosion.mp3" };
		static constexpr dae::SoundEntry s_BombDeployedSoundEntry{ "Sounds/BombDeploy.wav" };
		static constexpr dae::SoundEntry s_PowerUpSoundEntry{ "Sounds/PowerUp.wav" };

	};
}

#endif // !LEVELSOUNDSPLAYER_H

