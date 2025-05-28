#include "TextureSystem.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "ServiceLocator.h"

//===================================================================================================================================================
//SDL_SoundSystem
//===================================================================================================================================================

dae::SDL_TextureSystem::SDL_TextureSystem(const std::filesystem::path& dataPath, SDL_Renderer* pRenderer)
	:m_DataPath{ dataPath }
	, m_pRenderer{ pRenderer }
{
	if (m_pRenderer == nullptr)
		throw std::runtime_error("nullprt passed as SDL renderer to SDL_TextureSystem");
}

std::unique_ptr<dae::Texture2D> dae::SDL_TextureSystem::CreateTextTexture()
{
	return std::make_unique<Texture2D>(m_pRenderer);
}

//Unload all textures where token amount is 0
//This is the only way to delete unused textures!
void dae::SDL_TextureSystem::UnloadUnusedResources()  
{  
	std::erase_if(m_ImageTextures, [](const auto& pair) {
		return pair.second.tokenAmount == 0;
		});
}

//Adds a texture to the map OR finds the texture if it already exists
//Returns the pointer to the texture and increments the token amount
std::pair<dae::Texture2D*, bool> dae::SDL_TextureSystem::RegisterTexture(const TextureEntry& textureEntry)
{
	auto loc = m_ImageTextures.find(textureEntry.id);
	if (loc != m_ImageTextures.end())
	{
		loc->second.tokenAmount++;
		return { loc->second.pTexture.get(), true };
	}

	std::string path = m_DataPath.string();
	path += textureEntry.path;
	auto [newLoc, succes] = m_ImageTextures.emplace(textureEntry.id, TextureResource(path, m_pRenderer));
	if (!succes)
	{
		std::cout << std::format("Failed to insert texture into map. (entryID: {}, path: {}\n)", textureEntry.id, path);
		return { nullptr, false };
	}
	newLoc->second.tokenAmount++;
	return { newLoc->second.pTexture.get(), true };
}

//Decrements the token amount of the texture
void dae::SDL_TextureSystem::UnregisterTexture(texture_id id)
{
	auto loc = m_ImageTextures.find(id);
	if (loc == m_ImageTextures.end())
	{
		std::cout << std::format("Failed to find texture to unload with id: {}\n", id);
		return;
	}
	loc->second.tokenAmount--;
}

dae::Texture2D* dae::SDL_TextureSystem::GetTexture(texture_id id) const
{
	auto loc = m_ImageTextures.find(id);
	if (loc == m_ImageTextures.end())
	{
		std::cout << std::format("Failed to find texture with id: {}\n", id);
		return nullptr;
	}
	return loc->second.pTexture.get();
}