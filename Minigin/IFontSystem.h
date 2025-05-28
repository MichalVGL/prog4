#ifndef IFONTSYSTEM_H
#define IFONTSYSTEM_H

#include <utility>

#include "FontDefines.h"
#include "FontEntry.h"



namespace dae
{
	class FontToken;
	class Font;

	class IFontSystem
	{
	public:
		virtual ~IFontSystem() = default;

		virtual void UnloadUnusedResources() = 0;

	protected:
		friend class FontToken;

		virtual std::tuple<Font*, FontFullID, bool> RegisterFont(const FontEntry& fontEntry, font_size size) = 0;	//returns true if succesfull
		virtual void UnregisterFont(FontFullID id) = 0;

		virtual Font* GetFont(FontFullID id) const = 0;
		virtual FontFullID GetFontFullID(const FontEntry& fontEntry, font_size size) const = 0;
	};
}
#endif // !IFONTSYSTEM_H
