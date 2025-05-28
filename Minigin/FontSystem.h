#ifndef FONTSYSTEM_H
#define FONTSYSTEM_H

#include <memory>
#include <filesystem>
#include <unordered_map>

#include "IFontSystem.h"
#include "FontEntry.h"
#include "Font.h"

namespace dae
{
	struct FontResource
	{
		std::unique_ptr<Font> pFont;
		int tokenAmount{ 0 };

		FontResource(const std::string& path, font_size size)
			: pFont{ std::make_unique<Font>(path, size) }
		{
		}
	};

	//Null_FontSystem=====================================================================================================

	class Null_FontSystem final : public IFontSystem
	{
	public:

		void UnloadUnusedResources() override {};

	private:

		std::tuple<Font*, FontFullID, bool> RegisterFont(const FontEntry&, font_size) override { return { nullptr, FontFullID(), false }; };
		void UnregisterFont(FontFullID) override {};

		Font* GetFont(FontFullID) const override { return nullptr; };
		FontFullID GetFontFullID(const FontEntry&, font_size) const override { return FontFullID(); };
	};

	//SDL_FontSystem=====================================================================================================

	class SDL_FontSystem final : public IFontSystem
	{
	public:

		SDL_FontSystem(const std::filesystem::path& dataPath);

		~SDL_FontSystem();

		SDL_FontSystem(const SDL_FontSystem&) = delete;
		SDL_FontSystem& operator=(const SDL_FontSystem&) = delete;
		SDL_FontSystem(SDL_FontSystem&&) = default;
		SDL_FontSystem& operator=(SDL_FontSystem&&) = default;

		void UnloadUnusedResources() override;

	private:

		std::tuple<Font*, FontFullID, bool> RegisterFont(const FontEntry& fontEntry, font_size size) override;
		void UnregisterFont(FontFullID id) override;

		Font* GetFont(FontFullID id) const override;
		FontFullID GetFontFullID(const FontEntry& fontEntry, font_size size) const override;

		std::filesystem::path m_DataPath;
		std::unordered_map<FontFullID, FontResource> m_Fonts;
	};

}

#endif // !FONTSYSTEM_H


