#ifndef IRENDERSYSTEM_H
#define IRENDERSYSTEM_H

#include "RenderStructs.h"
#include "Texture2D.h"
#include "Utils.h"

struct SDL_Renderer;

namespace dae
{
	class IRenderSystem
	{
	public:

		virtual ~IRenderSystem() = default;

		virtual void Quit() = 0;

		virtual SDL_Renderer* GetSDLRenderer() const = 0;

		virtual void Render() const = 0;
		virtual void SetBackgroundColor(Color color) = 0;

		virtual void RenderTexture(const Texture2D& texture, float x, float y) const = 0; 
		virtual void RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y) const = 0;
		virtual void RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect) const = 0; 
	};
}

#endif 