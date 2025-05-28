#ifndef TEXTUREENTRY_H
#define TEXTUREENTRY_H

#include "ResourceEntry.h"
#include "TextureDefines.h"

//todo make a texttoken that contains a fonttoken and a texturetoken, only expose the fontentry to the user and hide the token

namespace dae
{
	struct TextureEntry final : public ResourceEntry<dae::texture_id>
	{
		template <size_t N>
		constexpr TextureEntry(const char(&path)[N])
			: ResourceEntry(path)
		{
		}
	};
}

#endif // TEXTUREENTRY_H
