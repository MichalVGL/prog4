#ifndef ISOUNDSYSTEM_H
#define ISOUNDSYSTEM_H

#include <string>

#include "SoundDefines.h"
#include "SoundEntry.h"

namespace dae
{
	class SoundToken;

	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;

		virtual void Quit() = 0;

		virtual void SetGlobalVolume(sound_volume volume) = 0;

	protected:

		friend class SoundToken;
		friend class Logger_SoundSystem;

		//should only be called by the token
		virtual void PlayEffect(const SoundToken& soundToken, sound_volume volume, sound_loops loops) = 0;	
		virtual void StopEffect(const SoundToken& soundToken) = 0;
		virtual bool IsPlayingEffect(const SoundToken& soundToken) const = 0;
		virtual void RegisterSound(const SoundEntry& soundEntry) = 0;
		virtual void UnregisterSound(sound_id id) = 0;
	};
}	

#endif // !ISOUNDSYSTEM_H

