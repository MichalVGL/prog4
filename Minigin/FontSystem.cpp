#include "FontSystem.h"

#include <algorithm>
#include <iostream>

//===================================================================================================================================================
//SDL_FontSystem
//===================================================================================================================================================

#include <SDL.h>
#include <SDL_ttf.h>

dae::SDL_FontSystem::SDL_FontSystem(const std::filesystem::path& dataPath)
	:m_DataPath{ dataPath }
{
	if (TTF_Init() == -1)
	{
		std::cout << std::format("Failed to initialize SDL_ttf: {}\n", TTF_GetError());
		return;
	}
}

void dae::SDL_FontSystem::Quit()
{
	m_Fonts.clear();
	TTF_Quit();
}

void dae::SDL_FontSystem::UnloadUnusedResources()
{
	std::erase_if(m_Fonts, [](const auto& pair) {
		return pair.second.tokenAmount == 0;
		});
}

std::tuple<dae::Font*, dae::FontFullID, bool> dae::SDL_FontSystem::RegisterFont(const FontEntry& fontEntry, font_size size)
{
	auto loc = m_Fonts.find(FontFullID{ .id = fontEntry.id, .size = size });

	if (loc != m_Fonts.end())
	{
		loc->second.tokenAmount++;
		return { loc->second.pFont.get(), loc->first, true };	//already exists
	}

	std::string path = m_DataPath.string();
	path += fontEntry.path;
	auto [newLoc, succes] = m_Fonts.emplace(FontFullID{ .id = fontEntry.id, .size = size}, FontResource(path, size));
	if (!succes)
	{
		std::cout << std::format("Failed to insert font into map. (id: {}, path: {}\n)", fontEntry.id, path);
		return { nullptr, FontFullID(), false};
	}

	return { newLoc->second.pFont.get(), newLoc->first, true };
}

void dae::SDL_FontSystem::UnregisterFont(FontFullID id)
{
	auto loc = m_Fonts.find(id);
	if (loc == m_Fonts.end())
	{
		std::cout << std::format("Failed to find font to unload with id: {}\n", id.id);
		return;
	}
	loc->second.tokenAmount--;
}

dae::Font* dae::SDL_FontSystem::GetFont(FontFullID id) const
{
	auto loc = m_Fonts.find(id);
	if (loc == m_Fonts.end())
	{
		std::cout << std::format("Failed to find font with id: {}\n", id.id);
		return nullptr;
	}

	return loc->second.pFont.get();
}

dae::FontFullID dae::SDL_FontSystem::GetFontFullID(const FontEntry& fontEntry, font_size size) const
{
	return FontFullID{.id = fontEntry.id, .size = size};
}
