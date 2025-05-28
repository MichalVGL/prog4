#include "RenderSystem.h"

#include <stdexcept>
#include <iostream>
#include <format>

#include "SceneManager.h"
#include "ServiceLocator.h"

//===================================================================================================================================================
//SDL_RenderSystem
//===================================================================================================================================================

#include <SDL.h>

//Implementation==========================================================================

template<>
struct std::default_delete<SDL_Renderer>
{
	void operator()(SDL_Renderer* p) const
	{
		SDL_DestroyRenderer(p);
	}
};

template<>
struct std::default_delete<SDL_Window>
{
	void operator()(SDL_Window* p) const
	{
		SDL_DestroyWindow(p);
	}
};

namespace dae
{
	class SDL_RenderSystem::SDL_RenderSystemImpl final
	{
	public:

		SDL_RenderSystemImpl(const Window& window);

		~SDL_RenderSystemImpl();

		SDL_RenderSystemImpl(const SDL_RenderSystemImpl&) = delete;
		SDL_RenderSystemImpl& operator=(const SDL_RenderSystemImpl&) = delete;
		SDL_RenderSystemImpl(SDL_RenderSystemImpl&&) = delete;
		SDL_RenderSystemImpl& operator=(SDL_RenderSystemImpl&&) = delete;	

		SDL_Renderer* GetSDLRenderer() const;

		void Render() const;
		void SetBackgroundColor(SDL_Color color);

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y) const;
		void RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect) const;

	private:

		static int GetOpenGLDriverIndex();

		std::unique_ptr<SDL_Window> m_pSDLWindow;
		Window m_Window;	//used to keep data on height,...

		std::unique_ptr<SDL_Renderer> m_pRenderer{};

		SDL_Color m_BackgroundColor{};
		float m_RenderScale;
	};
}

dae::SDL_RenderSystem::SDL_RenderSystemImpl::SDL_RenderSystemImpl(const Window& window)
	:m_Window{ window }
	, m_RenderScale{ window.renderScale }
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pSDLWindow = std::unique_ptr<SDL_Window>{
		SDL_CreateWindow(window.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			static_cast<int>(window.w * window.renderScale), static_cast<int>(window.h * window.renderScale), SDL_WINDOW_SHOWN) };

	m_pRenderer = std::unique_ptr<SDL_Renderer>{ SDL_CreateRenderer(m_pSDLWindow.get(), GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED) };
	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

dae::SDL_RenderSystem::SDL_RenderSystemImpl::~SDL_RenderSystemImpl()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Renderer* dae::SDL_RenderSystem::SDL_RenderSystemImpl::GetSDLRenderer() const
{
	return m_pRenderer.get();
}

void dae::SDL_RenderSystem::SDL_RenderSystemImpl::Render() const
{
	const auto& color = m_BackgroundColor;
	SDL_SetRenderDrawColor(m_pRenderer.get(), color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_pRenderer.get());

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_pRenderer.get());
}

void dae::SDL_RenderSystem::SDL_RenderSystemImpl::SetBackgroundColor(SDL_Color color)
{
	m_BackgroundColor = color;
}

void dae::SDL_RenderSystem::SDL_RenderSystemImpl::RenderTexture(const Texture2D& texture, float x, float y) const  
{  
   Rect srcRect{ 0, 0, texture.GetWidth(), texture.GetHeight() };  
   Rect dstRect{ static_cast<int>(x), static_cast<int>(y), texture.GetWidth(), texture.GetHeight() };  
   RenderTexture(texture, srcRect, dstRect);  
}

void dae::SDL_RenderSystem::SDL_RenderSystemImpl::RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y) const
{
	Rect dstRect{ static_cast<int>(x), static_cast<int>(y), srcRect.w, srcRect.h };
	RenderTexture(texture, srcRect, dstRect);
}

void dae::SDL_RenderSystem::SDL_RenderSystemImpl::RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect) const
{
	SDL_Rect src{
		.x = srcRect.x,
		.y = texture.GetHeight() - srcRect.y - srcRect.h,	//change origin to bottom-left (in the texture itself)
		.w = srcRect.w,
		.h = srcRect.h };
	
	SDL_Rect dst{
		.x = static_cast<int>(dstRect.x * m_RenderScale),
		.y = static_cast<int>((m_Window.h - dstRect.y - dstRect.h) * m_RenderScale),	//change origin to bottom-left (of the window)
		.w = static_cast<int>(dstRect.w * m_RenderScale),
		.h = static_cast<int>(dstRect.h * m_RenderScale) };

#ifdef _DEBUG
	if (SDL_RenderCopy(m_pRenderer.get(), texture.GetSDLTexture(), &src, &dst))	//if there is an error
	{
		std::cout << std::format("SDL_RenderCopy failed: {}\n", SDL_GetError());
	}
#else
	SDL_RenderCopy(m_pRenderer.get(), texture.GetSDLTexture(), &src, &dst);
#endif // DEBUG
}

//static
int dae::SDL_RenderSystem::SDL_RenderSystemImpl::GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}
//Base class==============================================================================

dae::SDL_RenderSystem::SDL_RenderSystem(const Window& window)
	: m_pSDLRenderSystemImpl{ std::make_unique<SDL_RenderSystemImpl>(window) }
{
}

dae::SDL_RenderSystem::~SDL_RenderSystem() = default;

SDL_Renderer* dae::SDL_RenderSystem::GetSDLRenderer() const
{
	return m_pSDLRenderSystemImpl->GetSDLRenderer();
}

void dae::SDL_RenderSystem::Render() const
{
	m_pSDLRenderSystemImpl->Render();
}

void dae::SDL_RenderSystem::SetBackgroundColor(Color color)
{
	m_pSDLRenderSystemImpl->SetBackgroundColor(SDL_Color{ color.r, color.g, color.b, color.a });
}

void dae::SDL_RenderSystem::RenderTexture(const Texture2D& texture, float x, float y) const
{
	m_pSDLRenderSystemImpl->RenderTexture(texture, x, y);
}

void dae::SDL_RenderSystem::RenderTexture(const Texture2D& texture, Rect srcRect, float x, float y) const
{
	m_pSDLRenderSystemImpl->RenderTexture(texture, srcRect, x, y);
}

void dae::SDL_RenderSystem::RenderTexture(const Texture2D& texture, Rect srcRect, Rect dstRect) const
{
	m_pSDLRenderSystemImpl->RenderTexture(texture, srcRect, dstRect);
}
