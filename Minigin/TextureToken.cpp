#include "TextureToken.h"
#include <stdexcept>

dae::TextureToken::~TextureToken()
{
	if(m_pTextureEntry)
		ServiceLocator::GetTextureSystem().UnregisterTexture(m_pTextureEntry->id);
}

dae::TextureToken::TextureToken(TextureToken&& other) noexcept
	:m_pRenderSystem{ other.m_pRenderSystem }
	, m_pTextureEntry{ other.m_pTextureEntry }
	, m_pTexture{ other.m_pTexture }
{
	other.m_pRenderSystem = nullptr;
	other.m_pTextureEntry = nullptr;
	other.m_pTexture = nullptr;
}

dae::TextureToken& dae::TextureToken::operator=(TextureToken&& other) noexcept
{
	if (this != &other)
	{
		if (m_pTextureEntry)
			ServiceLocator::GetTextureSystem().UnregisterTexture(m_pTextureEntry->id);

		m_pRenderSystem = other.m_pRenderSystem;
		m_pTextureEntry = other.m_pTextureEntry;
		m_pTexture = other.m_pTexture;
		other.m_pRenderSystem = nullptr;
		other.m_pTextureEntry = nullptr;
		other.m_pTexture = nullptr;
	}
	return *this;
}

void dae::TextureToken::LoadImageTexture(const TextureEntry& entry)
{
	if (m_pTextureEntry)
		ServiceLocator::GetTextureSystem().UnregisterTexture(m_pTextureEntry->id);

	m_pTextureEntry = &entry;
	auto [pTexture, succes] = ServiceLocator::GetTextureSystem().RegisterTexture(*m_pTextureEntry);
	if (succes == false or pTexture == nullptr)
		throw std::runtime_error("Failed to load texture");

	m_pTexture = pTexture;
}

glm::ivec2 dae::TextureToken::GetSize() const
{
	if (m_pTexture)
	{
		return { m_pTexture->GetWidth(), m_pTexture->GetHeight() };
	}
	else
	{
		return { 0, 0 };
	}
}

void dae::TextureToken::Render(float x, float y) const
{
	if (m_pTexture)
	{
		m_pRenderSystem->RenderTexture(*m_pTexture, x, y);
	}
}

void dae::TextureToken::Render(Rect srcRect, float x, float y) const
{
	if (m_pTexture)
	{
		m_pRenderSystem->RenderTexture(*m_pTexture, srcRect, x, y);
	}
}

void dae::TextureToken::Render(Rect srcRect, Rect dstRect) const
{
	if (m_pTexture)
	{
		m_pRenderSystem->RenderTexture(*m_pTexture, srcRect, dstRect);
	}
}
