#include "Texture2D.h"


#include <stdexcept>
#include <glm.hpp>
#include <iostream>
#include <format>
#include <cassert>

#include "ServiceLocator.h"
#include "Font.h"

//====================================================================
// SDL Impl Declaration
//====================================================================

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

template<>
struct std::default_delete<SDL_Texture>
{
	void operator()(SDL_Texture* p) const
	{
		SDL_DestroyTexture(p);
	}
};

namespace dae
{
	class Texture2D::SDL_Texture2DImpl final
	{
	public:

		SDL_Texture2DImpl(SDL_Renderer* renderer);

		SDL_Texture* GetSDLTexture() const;

		bool LoadImage2D(const std::string& fullPath);
		bool LoadText(const std::string& text, const Font* font, Color color);

		int GetWidth() const;
		int GetHeight() const;
		Flip GetFlip() const;
		texture_angle GetAngle() const;

		void SetHorizontalFlip(bool flip);
		void SetVerticalFlip(bool flip);
		void SetAngle(texture_angle angle);

	private:

		std::unique_ptr<SDL_Texture> m_pTexture{};
		SDL_Renderer* m_pRenderer;
		Flip m_Flip{};
		texture_angle m_Angle{0.0};
		glm::ivec2 m_Size{};
	};
}

//====================================================================
// SDL Definitions
//====================================================================

//image constructor
dae::Texture2D::SDL_Texture2DImpl::SDL_Texture2DImpl(SDL_Renderer* renderer)
	:m_pRenderer{ renderer }
{
	if (m_pRenderer == nullptr)
		throw std::runtime_error("nullptr passed as SDL renderer to SDL_Texture2DImpl");
}

SDL_Texture* dae::Texture2D::SDL_Texture2DImpl::GetSDLTexture() const
{
	return m_pTexture.get();
}

bool dae::Texture2D::SDL_Texture2DImpl::LoadImage2D(const std::string& fullPath)
{
	assert(m_pTexture == nullptr && "Texture already loaded, a Texture2D shouldn't load a texture again due to how texturesystem works (id-system)");

	m_pTexture = std::unique_ptr<SDL_Texture>(IMG_LoadTexture(m_pRenderer, fullPath.c_str()));
	if (m_pTexture == nullptr)
	{
		std::cout << std::format("Failed to load texture: {}\n", SDL_GetError());
		return false;
	}

	SDL_QueryTexture(m_pTexture.get(), nullptr, nullptr, &m_Size.x, &m_Size.y);
	return true;
}

bool dae::Texture2D::SDL_Texture2DImpl::LoadText(const std::string& text, const Font* font, Color color)
{
	if (font == nullptr)
	{
		std::cout << std::format("nullptr passed as font to SDL_Texture2DImpl::LoadText\n");
		return false;
	}

	SDL_Color sdlColor = { color.r, color.g, color.b, color.a };
	SDL_Surface* pSurface = TTF_RenderText_Blended(font->GetSDLFont(), text.c_str(), sdlColor);
	if (pSurface == nullptr)
	{
		std::cout << std::format("Failed to create surface from text: {}\n", TTF_GetError());
		return false;
	}

	m_pTexture = std::unique_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(m_pRenderer, pSurface));
	SDL_FreeSurface(pSurface);
	if (m_pTexture == nullptr)
	{
		std::cout << std::format("Failed to create texture from surface: {}\n", SDL_GetError());
		return false;
	}
	SDL_SetTextureBlendMode(m_pTexture.get(), SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture.get(), nullptr, nullptr, &m_Size.x, &m_Size.y);
	return true;
}

int dae::Texture2D::SDL_Texture2DImpl::GetWidth() const
{
	return m_Size.x;
}

int dae::Texture2D::SDL_Texture2DImpl::GetHeight() const
{
	return m_Size.y;
}

dae::Flip dae::Texture2D::SDL_Texture2DImpl::GetFlip() const
{
	return m_Flip;
}

dae::texture_angle dae::Texture2D::SDL_Texture2DImpl::GetAngle() const
{
	return m_Angle;
}

void dae::Texture2D::SDL_Texture2DImpl::SetHorizontalFlip(bool flip)
{
	m_Flip.horizontal = flip;
}

void dae::Texture2D::SDL_Texture2DImpl::SetVerticalFlip(bool flip)
{
	m_Flip.vertical = flip;
}

void dae::Texture2D::SDL_Texture2DImpl::SetAngle(texture_angle angle)
{
	m_Angle = angle;
}

//====================================================================
// Base Texture2D
//====================================================================

dae::Texture2D::Texture2D(SDL_Renderer* renderer)
	:m_pSDLTextureImpl{ std::make_unique<SDL_Texture2DImpl>(renderer) }
{
}

dae::Texture2D::~Texture2D() = default;
dae::Texture2D::Texture2D(Texture2D&&) noexcept = default;
dae::Texture2D& dae::Texture2D::operator=(Texture2D&&) noexcept = default;

bool dae::Texture2D::LoadImage2D(const std::string& fullPath)
{
	return m_pSDLTextureImpl->LoadImage2D(fullPath);
}

bool dae::Texture2D::LoadText(const std::string& text, const Font* font, Color color)
{
	return m_pSDLTextureImpl->LoadText(text, font, color);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pSDLTextureImpl->GetSDLTexture();
}

int dae::Texture2D::GetWidth() const
{
	return m_pSDLTextureImpl->GetWidth();
}

dae::Flip dae::Texture2D::GetFlip() const
{
	return m_pSDLTextureImpl->GetFlip();
}

dae::texture_angle dae::Texture2D::GetAngle() const
{
	return m_pSDLTextureImpl->GetAngle();
}

void dae::Texture2D::SetHorizontalFlip(bool flip)
{
	m_pSDLTextureImpl->SetHorizontalFlip(flip);
}

void dae::Texture2D::SetVerticalFlip(bool flip)
{
	m_pSDLTextureImpl->SetVerticalFlip(flip);
}

void dae::Texture2D::SetAngle(texture_angle angle)
{
	m_pSDLTextureImpl->SetAngle(angle);
}

int dae::Texture2D::GetHeight() const
{
	return m_pSDLTextureImpl->GetHeight();
}