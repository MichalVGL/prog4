//---------------------------
// Include Files
//---------------------------
#include <iostream>
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Font.h"
#include "GameObject.h"
#include "ImageRenderComp.h"
#include "Renderer.h"
#include "Texture2DO.h"

#include "ServiceLocator.h"

//---------------------------
// Constructor & Destructor
//---------------------------

using namespace dae;

TextComp::TextComp(dae::GameObject& parent, const std::shared_ptr<dae::Font>& font)
	: Component{ parent }
	, m_OldFont{ font }
	, m_OldTextTexture{}
	, m_pTextTexture{ std::make_unique<Texture2D>(ServiceLocator::GetRenderSystem().GetSDLRenderer()) }
{
}

void TextComp::Start()
{
	m_pRenderComp = GetOwnerComponent<ImageRenderComp>();
}

void TextComp::Update(float)
{
	if (m_FontNeedsUpdate)
	{
		m_FontNeedsUpdate = false;

		if (m_pFontEntry)
		{
			m_FontToken.LoadFont(*m_pFontEntry, m_FontSize);
		}

		m_NeedsUpdate = true;
	}

	if (m_NeedsUpdate)
	{
		m_NeedsUpdate = false;

		if (m_Text.length() == 0 || m_FontToken.GetFont() == nullptr)
		{
			return;
		}

		m_pTextTexture->LoadText(m_Text, m_FontToken.GetFont(), m_FgColor);
		m_pRenderComp->LoadTextTexture(m_pTextTexture.get());

		//todo delete
		const SDL_Color color = { m_FgColor.r, m_FgColor.g, m_FgColor.b, m_FgColor.a };
		const auto surf = TTF_RenderText_Blended(m_OldFont->GetSDLFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		
		m_OldTextTexture = m_pRenderComp->LoadTexture(texture);
		//

		//m_pRenderComp
	}
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComp::SetFont(const std::shared_ptr<dae::Font>& font)
{	//todo delete
	m_OldFont = font;
	m_NeedsUpdate = true;
}

void dae::TextComp::SetFont(const FontEntry& fontEntry)
{
	m_pFontEntry = &fontEntry;
	m_FontNeedsUpdate = true;
}

void dae::TextComp::SetSize(font_size size)
{
	m_FontSize = size;
	m_FontNeedsUpdate = true;
}

void dae::TextComp::SetColor(Color color)
{
	m_FgColor = color;
	m_NeedsUpdate = true;
}
