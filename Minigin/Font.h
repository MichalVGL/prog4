#ifndef FONT_H
#define FONT_H

#include <memory>
#include <string>

#include "FontDefines.h"

struct _TTF_Font;
namespace dae
{
	class Font final
	{
	public:
		Font(const std::string& fullPath, font_size size);
		~Font();

		Font(const Font&) = delete;
		Font& operator=(const Font&) = delete;
		Font(Font&&) noexcept;
		Font& operator=(Font&&) noexcept;

		_TTF_Font* GetSDLFont() const;

	private:

		class SDL_FontImpl;
		std::unique_ptr<SDL_FontImpl> m_pSDLFontImpl;
	};
}

#endif // FONT_H