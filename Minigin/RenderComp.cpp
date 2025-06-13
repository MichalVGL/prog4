#include "RenderComp.h"
#include "GameObject.h"
#include "TransformComp.h"

#include "ServiceLocator.h"

using namespace dae;

RenderComp::RenderComp(dae::GameObject& parent)
	:Component{ parent }
{
}

void RenderComp::Start()
{
	m_TransformComp.Init(GetOwner());
}

void RenderComp::Render() const
{
	glm::vec2 pos{ GetOwner().GetWorldPos() + m_AlignmentOffset };

	Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y), m_RenderSize.x, m_RenderSize.y };

	Texture2D* pTexture = GetTexture();

	if (pTexture)
		m_pRenderSystem->RenderTexture(*pTexture, m_SrcRect, dstRect, m_RenderParams);
}

void dae::RenderComp::LoadImageTexture(const TextureEntry& entry)	//will reset rendersize
{
	if (CheckLock())
		return;

	m_TextureData = std::move(TextureToken{});

	auto& token = std::get<TextureToken>(m_TextureData);

	token.LoadImageTexture(entry);
	auto pTexture = token.GetTexture();
	if (pTexture)
	{
		SetSrcRect(Rect{ 0, 0, pTexture->GetWidth(), pTexture->GetHeight() });
	}

}

void dae::RenderComp::LoadTextTexture(Texture2D* text)	//will reset rendersize
{
	if (CheckLock())
		return;

	if (text != nullptr)
	{
		m_TextureData = text;
		SetSrcRect({ 0, 0, text->GetWidth(), text->GetHeight() });
	}
	else
	{
		std::cout << "RenderComp::LoadTextTexture: nullptr passed as text texture\n";
	}
}

void RenderComp::UnloadTexture()
{
	m_TextureData = nullptr;
}

dae::RenderKey dae::RenderComp::Lock()
{
	m_IsLocked = true;
	m_SavedKey = this;
	return m_SavedKey;
}

void dae::RenderComp::Unlock(RenderKey key)
{
	if (key == m_SavedKey)
		m_IsLocked = false;
	else
		std::cout << std::format("Warning: tried to unlock RenderComp with an invalid key. [GameObject: {}]\n", GetOwner().GetName());
}

void dae::RenderComp::SetSrcRect(Rect srcRect)
{
	m_SrcRect = srcRect;
	SetRenderSize({srcRect.w, srcRect.h});
	CalculateAlignmentOffset();
}

void dae::RenderComp::SetRenderSize(glm::ivec2 size)	//will reset on any texture change or SrcRect change
{
	m_RenderSize = size;
	CalculateAlignmentOffset();
}

void dae::RenderComp::SetHorizontalAlignment(HorizontalAlignment alignment)
{
	m_HorizontalAlignment = alignment;
	CalculateAlignmentOffset();
}

void dae::RenderComp::SetVerticalAlignment(VerticalAlignment alignment)
{
	m_VerticalAlignment = alignment;
	CalculateAlignmentOffset();
}

void dae::RenderComp::SetHorizontalFlip(bool flip)
{
	m_RenderParams.flip.horizontal = flip;
}

void dae::RenderComp::SetVerticalFlip(bool flip)
{
	m_RenderParams.flip.vertical = flip;
}

void dae::RenderComp::SetAngle(texture_angle angle)
{
	m_RenderParams.angle = angle;
}

glm::vec2 dae::RenderComp::GetTextureSize()
{
	auto* texture = GetTexture();
	if(!texture)
		return glm::vec2{ 0.f, 0.f };

	return glm::vec2(texture->GetWidth(), texture->GetHeight());
}

//==========================================================================
//class helpers
//==========================================================================

bool dae::RenderComp::CheckLock()
{
	if (m_IsLocked)
		std::cout << std::format("Tried assigning a new texture on a locked rendercomp. [{}]\n", GetOwner().GetName());
	return m_IsLocked;
}

Texture2D* dae::RenderComp::GetTexture() const
{
	if (auto* pImage = std::get_if<TextureToken>(&m_TextureData); pImage != nullptr)
		return pImage->GetTexture();
	else if (auto* pText = std::get_if<Texture2D*>(&m_TextureData); pText != nullptr)
		return *pText;
	return nullptr;
}

void dae::RenderComp::CalculateAlignmentOffset()
{
	if (m_RenderSize.x == 0 or m_RenderSize.y == 0)
		return;

	//corrected values
	float horizontalVal{ static_cast<float>(m_SrcRect.w) * (static_cast<float>(m_RenderSize.x) / static_cast<float>(m_SrcRect.w)) };
	float verticalVal{ static_cast<float>(m_SrcRect.h) * (static_cast<float>(m_RenderSize.y) / static_cast<float>(m_SrcRect.h)) };

	switch (m_HorizontalAlignment)
	{
	case dae::HorizontalAlignment::left:
		m_AlignmentOffset.x = 0.f;
		break;
	case dae::HorizontalAlignment::center:
		m_AlignmentOffset.x = -horizontalVal / 2.f;
		break;
	case dae::HorizontalAlignment::right:
		m_AlignmentOffset.x = -horizontalVal;
		break;
	}

	switch (m_VerticalAlignment)
	{
	case dae::VerticalAlignment::top:
		m_AlignmentOffset.y = -verticalVal;
		break;
	case dae::VerticalAlignment::center:
		m_AlignmentOffset.y = -verticalVal / 2.f;
		break;
	case dae::VerticalAlignment::bottom:
		m_AlignmentOffset.y = 0.f;
		break;
	}
}