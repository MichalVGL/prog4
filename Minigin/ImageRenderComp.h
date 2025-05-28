#ifndef RENDERCOMP_H
#define RENDERCOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <vector>
#include <glm.hpp>
#include <variant>

#include "Component.h"
#include "Texture.h"
#include "ServiceLocator.h"

namespace dae
{

	class TransformComp;

	class ImageRenderComp final : public Component
	{
	public:
		ImageRenderComp(dae::GameObject& parent);
		
		ImageRenderComp(const ImageRenderComp& other) = delete;
		ImageRenderComp(ImageRenderComp&& other) noexcept = delete;
		ImageRenderComp& operator=(const ImageRenderComp& other) = delete;
		ImageRenderComp& operator=(ImageRenderComp&& other)	noexcept = delete;\

		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;

		void Render() const override;

		void LoadImageTexture(const TextureEntry& entry);	//todo change name (and filename)
		void LoadTextTexture(Texture2D* text);
		void UnloadTexture();

		void SetSrcRect(Rect srcRect);

	private:

		TransformComp* m_pTransformComp;
		IRenderSystem* m_pRenderSystem{ &ServiceLocator::GetRenderSystem() };

		std::variant<
			Texture2D*,		//text (and default init to nullptr)
			TextureToken	//image
		> m_TextureData{ nullptr };

		Rect m_SrcRect{ 0, 0, 0, 0 };
	};
}
 
#endif // RENDERCOMP_H