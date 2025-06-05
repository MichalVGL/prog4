#include "ServiceLocator.h"

#include <cassert>

#include "SoundSystem.h"
#include "TextureSystem.h"
#include "RenderSystem.h"
#include "FontSystem.h"
#include "RandomSystem.h"

std::unique_ptr<dae::ISoundSystem> dae::ServiceLocator::m_pSoundSystem{ std::make_unique<dae::Null_SoundSystem>() };
std::unique_ptr<dae::ITextureSystem> dae::ServiceLocator::m_pTextureSystem{ std::make_unique<dae::Null_TextureSystem>() };
std::unique_ptr<dae::IRenderSystem> dae::ServiceLocator::m_pRenderSystem{ std::make_unique<dae::Null_RenderSystem>() };
std::unique_ptr<dae::IFontSystem> dae::ServiceLocator::m_pFontSystem{ std::make_unique<dae::Null_FontSystem>() };
std::unique_ptr<dae::IRandomSystem> dae::ServiceLocator::m_pRandomSystem{ std::make_unique<dae::Default_RandomSystem>() };

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem)
{
	assert(pSoundSystem != nullptr && "ServiceLocator::RegisterSoundSystem: Tried to register nullptr as SoundSystem");
	m_pSoundSystem = std::move(pSoundSystem);
}

dae::ISoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	if (!m_pSoundSystem)
	{
		m_pSoundSystem = std::make_unique<dae::Null_SoundSystem>();
	}
	return *m_pSoundSystem;
}

void dae::ServiceLocator::RegisterTextureSystem(std::unique_ptr<ITextureSystem>&& pTextureSystem)
{
	assert(pTextureSystem != nullptr && "ServiceLocator::RegisterTextureSystem: Tried to register nullptr as TextureSystem");
	m_pTextureSystem = std::move(pTextureSystem);
}

dae::ITextureSystem& dae::ServiceLocator::GetTextureSystem()
{
	if (!m_pTextureSystem)
	{
		m_pTextureSystem = std::make_unique<dae::Null_TextureSystem>();
	}
	return *m_pTextureSystem;
}

void dae::ServiceLocator::RegisterRenderSystem(std::unique_ptr<IRenderSystem>&& pRenderSystem)
{
	assert(pRenderSystem != nullptr && "ServiceLocator::RegisterRenderSystem: Tried to register nullptr as RenderSystem");
	m_pRenderSystem = std::move(pRenderSystem);
}

dae::IRenderSystem& dae::ServiceLocator::GetRenderSystem()
{
	if (!m_pRenderSystem)
	{
		m_pRenderSystem = std::make_unique<dae::Null_RenderSystem>();
	}
	return *m_pRenderSystem;
}

void dae::ServiceLocator::RegisterFontSystem(std::unique_ptr<IFontSystem>&& pFontSystem)
{
	assert(pFontSystem != nullptr && "ServiceLocator::RegisterFontSystem: Tried to register nullptr as FontSystem");
	m_pFontSystem = std::move(pFontSystem);
}

dae::IFontSystem& dae::ServiceLocator::GetFontSystem()
{
	if (!m_pFontSystem)
	{
		m_pFontSystem = std::make_unique<dae::Null_FontSystem>();
	}
	return *m_pFontSystem;
}

void dae::ServiceLocator::RegisterRandomSystem(std::unique_ptr<IRandomSystem>&& pRandomSystem)
{
	assert(pRandomSystem != nullptr && "ServiceLocator::RegisterRandomSystem: Tried to register nullptr as RandomSystem");
	m_pRandomSystem = std::move(pRandomSystem);
}

dae::IRandomSystem& dae::ServiceLocator::GetRandomSystem()
{
	if (!m_pRandomSystem)
	{
		m_pRandomSystem = std::make_unique<dae::Default_RandomSystem>();
	}
	return *m_pRandomSystem;
}
 