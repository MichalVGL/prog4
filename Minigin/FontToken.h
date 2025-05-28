#ifndef FONTTOKEN_H
#define FONTTOKEN_H

#include "FontDefines.h"
#include "FontEntry.h"
#include "Font.h"
#include "ServiceLocator.h"

namespace dae
{
	class FontToken final
	{
	public:

		FontToken() = default;
		~FontToken();

		FontToken(const FontToken&) = delete;
		FontToken& operator=(const FontToken&) = delete;
		FontToken(FontToken&&) = delete;
		FontToken& operator=(FontToken&&) = delete;

		void LoadFont(const FontEntry& entry, font_size size);
		Font* GetFont() const;

	private:

		FontFullID m_FullID{};
		Font* m_pFont{ nullptr };
		IFontSystem* m_pFontSystem{ &ServiceLocator::GetFontSystem() };
	};
}

#endif
