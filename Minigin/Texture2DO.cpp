#include <SDL.h>
#include <SDL_image.h>
#include "Texture2DO.h"
#include "Renderer.h"
#include <stdexcept>

dae::Texture2DO::~Texture2DO()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::Texture2DO::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::Texture2DO::GetSDLTexture() const
{
	return m_texture;
}

dae::Texture2DO::Texture2DO(const std::string &fullPath)
{
	m_texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (m_texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}

dae::Texture2DO::Texture2DO(SDL_Texture* texture)	: m_texture{ texture } 
{
	assert(m_texture != nullptr);
}

