#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <memory>
#include <string>

#include "RenderUtils.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace dae
{
	class Font;
	class Texture2D final
	{
	public:
		Texture2D(SDL_Renderer* renderer);

		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		//defaulted in cpp
		Texture2D(Texture2D&&) noexcept;
		Texture2D& operator=(Texture2D&&) noexcept;

		//returns true if succesfull
		bool LoadImage2D(const std::string& fullPath);
		bool LoadText(const std::string& text, const Font* font, Color color = {});

		SDL_Texture* GetSDLTexture() const;

		int GetHeight() const;
		int GetWidth() const;

	private:

		class SDL_Texture2DImpl;
		std::unique_ptr<SDL_Texture2DImpl> m_pSDLTextureImpl;
	};
}

#endif