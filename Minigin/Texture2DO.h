#ifndef TEXTURE2DO_H
#define TEXTURE2DO_H

#include <vec2.hpp>
#include <string>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2DO final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2DO(SDL_Texture* texture);
		explicit Texture2DO(const std::string& fullPath);
		~Texture2DO();

		glm::ivec2 GetSize() const;

		Texture2DO(const Texture2DO &) = delete;
		Texture2DO(Texture2DO &&) = delete;
		Texture2DO & operator= (const Texture2DO &) = delete;
		Texture2DO & operator= (const Texture2DO &&) = delete;
	private:
		SDL_Texture* m_texture;
	};
}

#endif // TEXTURE2DO_H