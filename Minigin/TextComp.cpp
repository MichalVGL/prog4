//---------------------------
// Include Files
//---------------------------
#include <iostream>
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Font.h"
#include "GameObject.h"
#include "RenderComp.h"
#include "Renderer.h"
#include "Texture2D.h"

//---------------------------
// Constructor & Destructor
//---------------------------
TextComp::TextComp(dae::GameObject& parent, const std::shared_ptr<dae::Font>& font)
	: Component{ parent }
	, m_pRenderComp{}
	, m_Text{}
	, m_Font{ font }
	, m_TextTexture{}
	, m_NeedsUpdate{ false }
{
}

void TextComp::Start()
{
	m_pRenderComp = GetOwnerComponent<RenderComp>();
}

void TextComp::Update(float)
{
	if (m_NeedsUpdate)
	{
		m_NeedsUpdate = false;

		if (m_Text.length() == 0)
		{
			return;
		}

		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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

		m_TextTexture = m_pRenderComp->LoadTexture(texture);
	}
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComp::SetFont(const std::shared_ptr<dae::Font>& font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}




