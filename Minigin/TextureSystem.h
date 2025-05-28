#ifndef TEXTURESYSTEM_H
#define TEXTURESYSTEM_H

#include <memory>
#include <filesystem>
#include <unordered_map>
#include <stdexcept>

#include "ITextureSystem.h"
#include "TextureToken.h"
#include "Texture2D.h"

struct SDL_Renderer;

namespace dae
{

	struct TextureResource
	{
		
		std::unique_ptr<Texture2D> pTexture;
		int tokenAmount{ 0 };

		TextureResource(const std::string& path, SDL_Renderer* pRenderer)
			: pTexture{ std::make_unique<Texture2D>(pRenderer) }
		{
			if (!pTexture->LoadImage2D(path))
			{
				throw std::runtime_error(std::format("Failed to load texture from path: {}\n", path));
			}
		}
	};


	//Null_TextureSystem=====================================================================================================
	class Null_TextureSystem final : public ITextureSystem
	{
	public:
		std::unique_ptr<Texture2D> CreateTextTexture() override { return nullptr; };

		void UnloadUnusedResources() override {};

	private:

		std::pair<Texture2D*, bool> RegisterTexture(const TextureEntry&) override { return { nullptr, false }; };
		void UnregisterTexture(texture_id) override {};
		Texture2D* GetTexture(texture_id) const override { return nullptr; };
	};

	//SDL_TextureSystem======================================================================================================
	class SDL_TextureSystem final : public ITextureSystem
	{
	public:

		SDL_TextureSystem(const std::filesystem::path& dataPath, SDL_Renderer* pRenderer);

		~SDL_TextureSystem() = default;
		SDL_TextureSystem(const SDL_TextureSystem&) = delete;
		SDL_TextureSystem& operator=(const SDL_TextureSystem&) = delete;
		SDL_TextureSystem(SDL_TextureSystem&&) = default;
		SDL_TextureSystem& operator=(SDL_TextureSystem&&) = default;

		std::unique_ptr<Texture2D> CreateTextTexture() override;

		void UnloadUnusedResources() override;

	private:

		std::pair<Texture2D*, bool> RegisterTexture(const TextureEntry& textureEntry) override;
		void UnregisterTexture(texture_id id) override;
		Texture2D* GetTexture(texture_id id) const override;

		std::filesystem::path m_DataPath;
		SDL_Renderer* m_pRenderer;

		std::unordered_map<texture_id, TextureResource> m_ImageTextures;

	};
}

#endif // !TEXTURESYSTEM_H