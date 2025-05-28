//---------------------------
// Include Files
//---------------------------
#include <iostream>
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Font.h"
#include "GameObject.h"
#include "ImageRenderComp.h"
#include "ServiceLocator.h"

//---------------------------
// Constructor & Destructor
//---------------------------

using namespace dae;

TextComp::TextComp(dae::GameObject& parent)
	: Component{ parent }
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
	}
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;
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
