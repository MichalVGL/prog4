//---------------------------
// Include Files
//---------------------------
#include <iostream>
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Font.h"
#include "GameObject.h"
#include "RenderComp.h"
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
	m_RenderComp.Init(GetOwner());
}

void TextComp::Update(float)
{
	//update fornt if needed
	if (m_FontNeedsUpdate)
	{
		m_FontNeedsUpdate = false;

		if (m_pFontEntry)
		{
			m_FontToken.LoadFont(*m_pFontEntry, m_FontSize);
		}

		m_NeedsUpdate = true;
	}

	//handle the function
	if (m_Mode == TextMode::textFunc && m_TextFunc)
	{
		std::string newText = m_TextFunc();
		if (m_Text != newText)
		{
			m_NeedsUpdate = true;
			m_Text = std::move(newText);
		}
	}

	//update the texture if needed
	if (m_NeedsUpdate)
	{
		m_NeedsUpdate = false;

		if (m_Text.length() == 0 || m_FontToken.GetFont() == nullptr)
		{
			return;
		}

		m_pTextTexture->LoadText(m_Text, m_FontToken.GetFont(), m_FgColor);
		m_RenderComp->LoadTextTexture(m_pTextTexture.get());
	}
}

void TextComp::SetText(const std::string& text)
{
	if (m_Text != text || m_Mode == TextMode::textFunc)
	{
		m_NeedsUpdate = true;
		m_Text = text;
		m_Mode = TextMode::text;
	}
}

void dae::TextComp::SetTextFunc(std::function<std::string()> func)
{
	m_TextFunc = std::move(func);
	if (m_TextFunc)
	{
		m_Mode = TextMode::textFunc;
	}
	else
	{
		m_Mode = TextMode::text;
	}
}

void dae::TextComp::SetFont(const FontEntry& fontEntry)
{
	m_pFontEntry = &fontEntry;
	m_FontNeedsUpdate = true;
}

void dae::TextComp::SetSize(font_size size)
{
	if (m_FontSize != size)
	{
		m_FontSize = size;
		m_FontNeedsUpdate = true;
	}
}

void dae::TextComp::SetColor(Color color)
{
	m_FgColor = color;
	m_NeedsUpdate = true;
}
