#ifndef TEXTURETOKEN_H
#define TEXTURETOKEN_H

#include <glm.hpp>

#include "TextureDefines.h"
#include "TextureEntry.h"
#include "Texture2D.h"
#include "ServiceLocator.h"

namespace dae
{
	//used to count the amount of instances for a specific image (does not work for text!!!)
	class TextureToken final
	{
	public:

		TextureToken() = default;
		~TextureToken();

		TextureToken(const TextureToken&) = delete;
		TextureToken& operator=(const TextureToken&) = delete;
		TextureToken(TextureToken&&) noexcept;
		TextureToken& operator=(TextureToken&&) noexcept;

		void LoadImageTexture(const TextureEntry& entry);

		Texture2D* GetTexture() const;
		//glm::ivec2 GetSize() const;

	private:

		const TextureEntry* m_pTextureEntry{ nullptr };
		Texture2D* m_pTexture{ nullptr };
		IRenderSystem* m_pRenderSystem{ &ServiceLocator::GetRenderSystem() };
	};
}

#endif // !TEXTURETOKEN_H