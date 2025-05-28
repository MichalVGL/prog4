#ifndef TEXTURETOKEN_H
#define TEXTURETOKEN_H

#include <glm.hpp>

#include "TextureDefines.h"
#include "TextureEntry.h"
#include "Texture2D.h"
#include "ServiceLocator.h"

namespace dae
{
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

		glm::ivec2 GetSize() const;

		void Render(float x, float y) const;
		void Render(Rect srcRect, float x, float y) const;
		void Render(Rect srcRect, Rect dstRect) const;

	private:

		const TextureEntry* m_pTextureEntry{ nullptr };
		const Texture2D* m_pTexture{ nullptr };
		IRenderSystem* m_pRenderSystem{ &ServiceLocator::GetRenderSystem() };
	};
}

#endif // !TEXTURETOKEN_H