#ifndef TEXTUREENTRY_H
#define TEXTUREENTRY_H

#include "ResourceEntry.h"
#include "TextureDefines.h"

namespace dae
{
	//Make sure TextureEntry are alive at least as long as the tokens it creates

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
