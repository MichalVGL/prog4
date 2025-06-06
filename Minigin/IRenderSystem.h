#ifndef IRENDERSYSTEM_H
#define IRENDERSYSTEM_H

#include "RenderUtils.h"
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

		virtual void RenderTexture(const Texture2D& texture, float x, float y, RenderParams param) const = 0;
		virtual void RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y, RenderParams param) const = 0;
		virtual void RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect, RenderParams param) const = 0; 
	};
}

#endif 