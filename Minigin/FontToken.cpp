#include "FontToken.h"
#include <stdexcept>

dae::FontToken::~FontToken()
{
	if (m_pFont)
		m_pFontSystem->UnregisterFont(m_FullID);
}

void dae::FontToken::LoadFont(const FontEntry& entry, font_size size)
{
	if (m_pFont)
		m_pFontSystem->UnregisterFont(m_FullID);

	auto [pFont, id, succes] = m_pFontSystem->RegisterFont(entry, size);

	if(succes == false or pFont == nullptr)
		throw std::runtime_error("Failed to load font");

	m_pFont = pFont;
	m_FullID = id;
}

dae::Font* dae::FontToken::GetFont() const
{
	return m_pFont;
}