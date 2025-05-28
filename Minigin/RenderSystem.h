#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "IRenderSystem.h"

#include <memory>

namespace dae
{
	//Null_RenderSystem=====================================================================================================
	class Null_RenderSystem final : public IRenderSystem
	{
	public:

		SDL_Renderer* GetSDLRenderer() const override { return nullptr; };

		void Render() const override {};
		void SetBackgroundColor(Color) override {};

		void RenderTexture(const Texture2D&, float, float) const override {};
		void RenderTexture(const Texture2D&, Rect, float, float) const override {};
		void RenderTexture(const Texture2D&, Rect, Rect) const override {};

	};
}

//SDL_RenderSystem==========================================================================================================
namespace dae
{
	class SDL_RenderSystem final : public IRenderSystem
	{
	public:

		SDL_RenderSystem(const Window& window);

		~SDL_RenderSystem();	//defaulted in cpp

		SDL_RenderSystem(const SDL_RenderSystem&) = delete;
		SDL_RenderSystem& operator=(const SDL_RenderSystem&) = delete;
		SDL_RenderSystem(SDL_RenderSystem&&) = delete;
		SDL_RenderSystem& operator=(SDL_RenderSystem&&) = delete;

		SDL_Renderer* GetSDLRenderer() const override;

		void Render() const override;
		void SetBackgroundColor(Color color) override;

		void RenderTexture(const Texture2D& texture, float x, float y) const override;
		void RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y) const override;
		void RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect) const override;

	private:

		class SDL_RenderSystemImpl;
		std::unique_ptr<SDL_RenderSystemImpl> m_pSDLRenderSystemImpl;
	};

}

#endif // !RENDERSYSTEM_H