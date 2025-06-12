#include "LevelSoundsPlayer.h"

#include <ServiceLocator.h>

void bm::Default_LevelSoundsPlayer::PlaySound(LevelSound sound)
{
	m_RequestedSounds.insert(sound);
}

void bm::Default_LevelSoundsPlayer::Update()
{
	for (const auto& sound : m_RequestedSounds)
	{
		switch (sound)
		{
		case LevelSound::explosion:
			PlaySoundToken(m_ExplosionSoundToken);
			break;
		case LevelSound::bombDeployed:
			PlaySoundToken(m_BombDeployedSoundToken);
			break;
		case LevelSound::powerUp:
			PlaySoundToken(m_PowerUpSoundToken);
			break;
		}
	}

	m_RequestedSounds.clear();
}

//===============================================

void bm::Default_LevelSoundsPlayer::PlaySoundToken(dae::SoundToken& token)
{
	token.Stop();
	token.Play();
}
