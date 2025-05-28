#ifndef SOUNDENTRY_H
#define SOUNDENTRY_H

#include "SoundDefines.h"
#include "ResourceEntry.h"
#include "sdbmHash.h"

namespace dae
{
	struct SoundEntry final : public ResourceEntry<dae::sound_id>
	{
		// path is used as a relative path, the base path is set in the SoundSystem

		template <size_t N>
		constexpr SoundEntry(const char(&path)[N])
			: ResourceEntry(path)
		{
		}
	};
}
#endif // !SOUNDENTRY_H