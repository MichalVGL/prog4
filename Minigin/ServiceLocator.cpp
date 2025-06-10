#include "ServiceLocator.h"

#include <cassert>

#include "SoundSystem.h"
#include "TextureSystem.h"
#include "RenderSystem.h"
#include "FontSystem.h"
#include "RandomSystem.h"
#include "CameraSystem.h"
#include "SceneSystem.h"

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::s_pSoundSystem{ std::make_unique<dae::Null_SoundSystem>() };
std::unique_ptr<dae::ITextureSystem> dae::ServiceLocator::s_pTextureSystem{ std::make_unique<dae::Null_TextureSystem>() };
std::unique_ptr<dae::IRenderSystem> dae::ServiceLocator::s_pRenderSystem{ std::make_unique<dae::Null_RenderSystem>() };
std::unique_ptr<dae::IFontSystem> dae::ServiceLocator::s_pFontSystem{ std::make_unique<dae::Null_FontSystem>() };
std::unique_ptr<dae::IRandomSystem> dae::ServiceLocator::s_pRandomSystem{ std::make_unique<dae::Default_RandomSystem>() };
std::unique_ptr<dae::ICameraSystem> dae::ServiceLocator::s_pCameraSystem{ std::make_unique<dae::CameraSystem>() };
std::unique_ptr<dae::ISceneSystem> dae::ServiceLocator::s_pSceneSystem{ std::make_unique<dae::Null_SceneSystem>() };

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem)
{
	assert(pSoundSystem != nullptr && "ServiceLocator::RegisterSoundSystem: Tried to register nullptr as SoundSystem");
	s_pSoundSystem = std::move(pSoundSystem);
}

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	if (!s_pSoundSystem)
	{
		s_pSoundSystem = std::make_unique<dae::Null_SoundSystem>();
	}
	return *s_pSoundSystem;
}

void dae::ServiceLocator::RegisterTextureSystem(std::unique_ptr<ITextureSystem>&& pTextureSystem)
{
	assert(pTextureSystem != nullptr && "ServiceLocator::RegisterTextureSystem: Tried to register nullptr as TextureSystem");
	s_pTextureSystem = std::move(pTextureSystem);
}

dae::ITextureSystem& dae::ServiceLocator::GetTextureSystem()
{
	if (!s_pTextureSystem)
	{
		s_pTextureSystem = std::make_unique<dae::Null_TextureSystem>();
	}
	return *s_pTextureSystem;
}

void dae::ServiceLocator::RegisterRenderSystem(std::unique_ptr<IRenderSystem>&& pRenderSystem)
{
	assert(pRenderSystem != nullptr && "ServiceLocator::RegisterRenderSystem: Tried to register nullptr as RenderSystem");
	s_pRenderSystem = std::move(pRenderSystem);
}

dae::IRenderSystem& dae::ServiceLocator::GetRenderSystem()
{
	if (!s_pRenderSystem)
	{
		s_pRenderSystem = std::make_unique<dae::Null_RenderSystem>();
	}
	return *s_pRenderSystem;
}

void dae::ServiceLocator::RegisterFontSystem(std::unique_ptr<IFontSystem>&& pFontSystem)
{
	assert(pFontSystem != nullptr && "ServiceLocator::RegisterFontSystem: Tried to register nullptr as FontSystem");
	s_pFontSystem = std::move(pFontSystem);
}

dae::IFontSystem& dae::ServiceLocator::GetFontSystem()
{
	if (!s_pFontSystem)
	{
		s_pFontSystem = std::make_unique<dae::Null_FontSystem>();
	}
	return *s_pFontSystem;
}

void dae::ServiceLocator::RegisterRandomSystem(std::unique_ptr<IRandomSystem>&& pRandomSystem)
{
	assert(pRandomSystem != nullptr && "ServiceLocator::RegisterRandomSystem: Tried to register nullptr as RandomSystem");
	s_pRandomSystem = std::move(pRandomSystem);
}

dae::IRandomSystem& dae::ServiceLocator::GetRandomSystem()
{
	if (!s_pRandomSystem)
	{
		s_pRandomSystem = std::make_unique<dae::Default_RandomSystem>();
	}
	return *s_pRandomSystem;
}

void dae::ServiceLocator::RegisterCameraSystem(std::unique_ptr<ICameraSystem>&& pCameraSystem)
{
	assert(pCameraSystem != nullptr && "ServiceLocator::RegisterCameraSystem: Tried to register nullptr as CameraSystem");
	s_pCameraSystem = std::move(pCameraSystem);
}

dae::ICameraSystem& dae::ServiceLocator::GetCameraSystem()
{
	if (!s_pCameraSystem)
	{
		s_pCameraSystem = std::make_unique<dae::CameraSystem>();
	}
	return *s_pCameraSystem;
}

void dae::ServiceLocator::RegisterSceneSystem(std::unique_ptr<ISceneSystem>&& pSceneSystem)
{
	assert(pSceneSystem != nullptr && "ServiceLocator::RegisterSceneSystem: Tried to register nullptr as SceneSystem");
	s_pSceneSystem = std::move(pSceneSystem);
}

dae::ISceneSystem& dae::ServiceLocator::GetSceneSystem()
{
	if (!s_pSceneSystem)
	{
		s_pSceneSystem = std::make_unique<dae::Null_SceneSystem>();
	}
	return *s_pSceneSystem;
}
 