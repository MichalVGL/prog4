#include <stdexcept>
#include "Font.h"

//========================================================================================================================================
// SDL Impl
//========================================================================================================================================

#include <SDL.h>
#include <SDL_ttf.h>

template<>
struct std::default_delete<_TTF_Font>
{
	void operator()(_TTF_Font* p) const
	{
		TTF_CloseFont(p);
	}
};

namespace dae
{
	class Font::SDL_FontImpl final
	{
	public:

		SDL_FontImpl(const std::string& fullPath, font_size size);
		_TTF_Font* GetSDLFont() const;
	private:

		std::unique_ptr<_TTF_Font> m_pFont;
	};
}
//====================================================================
// SDL Definitions
//====================================================================

dae::Font::SDL_FontImpl::SDL_FontImpl(const std::string& fullPath, font_size size)
{
	m_pFont = std::unique_ptr<_TTF_Font>(TTF_OpenFont(fullPath.c_str(), size));
	if (m_pFont == nullptr)
		throw std::runtime_error(std::string("Failed to load font: ") + TTF_GetError());
}

_TTF_Font* dae::Font::SDL_FontImpl::GetSDLFont() const
{
	return m_pFont.get();
}

//========================================================================================================================================
// Base Font
//========================================================================================================================================

dae::Font::Font(const std::string& fullPath, font_size size)
	:m_pSDLFontImpl{ std::make_unique<SDL_FontImpl>(fullPath, size) }
{
}

dae::Font::~Font() = default;
dae::Font::Font(Font&&) noexcept = default;
dae::Font& dae::Font::operator=(Font&&) noexcept = default;

//SDL=======
_TTF_Font* dae::Font::GetSDLFont() const
{
	return m_pSDLFontImpl->GetSDLFont();
}
