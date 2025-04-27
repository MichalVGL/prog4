#ifndef ISOUNDSYSTEM_H
#define ISOUNDSYSTEM_H

#include <string>

#include "SoundDefines.h"
#include "SoundEntry.h"

namespace dae
{
	//todo add soundstream

	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;

		virtual void PlayEffect(const SoundEntry& soundEntry, sound_volume volume = 1.f) = 0;
	};
}	

#endif // !ISOUNDSYSTEM_H

