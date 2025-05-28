#ifndef ITEXTURESYSTEM_H
#define ITEXTURESYSTEM_H

#include <memory>

#include "TextureDefines.h"
#include "TextureEntry.h"

#include "FontDefines.h"

namespace dae
{
	class TextureToken;
	class Texture2D; 

	//Only image textures are used here, Text(from fonts) are owned in the TextToken itself

	class ITextureSystem
	{
	public:
		virtual ~ITextureSystem() = default;

		//Text is not owned by the texturesystem
		virtual std::unique_ptr<Texture2D> CreateTextTexture() = 0;

		virtual void UnloadUnusedResources() = 0;

	protected:

		friend class TextureToken;

		virtual std::pair<Texture2D*, bool> RegisterTexture(const TextureEntry& textureEntry) = 0;	//returns true if succesfull
		virtual void UnregisterTexture(texture_id id) = 0;
		virtual Texture2D* GetTexture(texture_id id) const = 0;
	};
}

#endif // ITEXTURESYSTEM_H