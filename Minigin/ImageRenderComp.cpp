//---------------------------
// Include Files
//---------------------------
#include "ImageRenderComp.h"
#include "GameObject.h"
#include "TransformComp.h"

#include "ServiceLocator.h"

using namespace dae;

ImageRenderComp::ImageRenderComp(dae::GameObject& parent)
	:Component{ parent }
	, m_pTransformComp{}
{
}

void ImageRenderComp::Start()
{
	m_pTransformComp = GetOwnerComponent<TransformComp>();
}

void ImageRenderComp::Render() const
{
	glm::vec2 pos{GetOwner().GetWorldPos()};

	if (auto* pImage = std::get_if<TextureToken>(&m_TextureData); pImage != nullptr)	//rendercomp is in image "mode"
	{
		pImage->Render(m_SrcRect, pos.x, pos.y);
	}
	else if (auto* pText = std::get_if<Texture2D*>(&m_TextureData); pText != nullptr)	//rendercomp is in text "mode"
	{
		if (*pText != nullptr)
		{
			m_pRenderSystem->RenderTexture(**pText, m_SrcRect, pos.x, pos.y);
		}
	}
}

void dae::ImageRenderComp::LoadImageTexture(const TextureEntry& entry)
{
	m_TextureData = std::move(TextureToken{});

	auto& token = std::get<TextureToken>(m_TextureData);

	token.LoadImageTexture(entry);
	auto size = token.GetSize();
	m_SrcRect = Rect{ 0, 0, size.x, size.y };	//set src rect to full texture
}

void dae::ImageRenderComp::LoadTextTexture(Texture2D* text)
{
	if (text == nullptr)
	{
		std::cout << "ImageRenderComp::LoadTextTexture: nullptr passed as text texture\n";
		return;
	}

	m_TextureData = text;
	m_SrcRect = Rect{ 0, 0, text->GetWidth(), text->GetHeight()};
}

void ImageRenderComp::UnloadTexture()
{
	m_TextureData = nullptr;
}

void dae::ImageRenderComp::SetSrcRect(Rect srcRect)
{
	m_SrcRect = srcRect;
}