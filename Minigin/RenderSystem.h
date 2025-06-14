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

		void Quit() override {};

		void Render() const override {};
		void SetBackgroundColor(Color) override {};
		void SetRenderOffset(glm::ivec2) override {};

		void RenderTexture(const Texture2D&, float, float, RenderParams) const override {};
		void RenderTexture(const Texture2D&, Rect, float, float, RenderParams) const override {};
		void RenderTexture(const Texture2D&, Rect, Rect, RenderParams) const override {};

		glm::vec2 GetCanvasSize() override { return glm::vec2(); };
	};
}

//SDL_RenderSystem==========================================================================================================
namespace dae
{
	class SDL_RenderSystem final : public IRenderSystem
	{
	public:

		SDL_RenderSystem(const Window& window);

		void Quit() override;

		~SDL_RenderSystem();	//defaulted in cpp

		SDL_RenderSystem(const SDL_RenderSystem&) = delete;
		SDL_RenderSystem& operator=(const SDL_RenderSystem&) = delete;
		SDL_RenderSystem(SDL_RenderSystem&&) = delete;
		SDL_RenderSystem& operator=(SDL_RenderSystem&&) = delete;

		SDL_Renderer* GetSDLRenderer() const override;

		void Render() const override;
		void SetBackgroundColor(Color color) override;
		void SetRenderOffset(glm::ivec2 offset) override;

		void RenderTexture(const Texture2D& texture, float x, float y, RenderParams param) const override;
		void RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y, RenderParams param) const override;
		void RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect, RenderParams param) const override;

		glm::vec2 GetCanvasSize() override;

	private:

		class SDL_RenderSystemImpl;
		std::unique_ptr<SDL_RenderSystemImpl> m_pSDLRenderSystemImpl;
	};

}

#endif // !RENDERSYSTEM_H