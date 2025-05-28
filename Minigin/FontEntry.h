#ifndef FONTENTRY_H
#define FONTENTRY_H

#include "ResourceEntry.h"
#include "FontDefines.h"

namespace dae
{
	struct FontEntry final : public ResourceEntry<dae::font_id>
	{
		template <size_t N>
		constexpr FontEntry(const char(&path)[N])
			: ResourceEntry(path)
		{
		}
	};
}

#endif // !FONTENTRY_H
