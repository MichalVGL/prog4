#ifndef RENDERCOMP_H
#define RENDERCOMP_H

#include <memory>
#include <vector>
#include <glm.hpp>
#include <variant>

#include "Component.h"
#include "Texture.h"
#include "ServiceLocator.h"

namespace dae
{
	class RenderComp;

	using RenderKey = RenderComp*;

	class TransformComp;

	class RenderComp final : public Component
	{
	public:
		RenderComp(dae::GameObject& parent);
		
		RenderComp(const RenderComp& other) = delete;
		RenderComp(RenderComp&& other) noexcept = delete;
		RenderComp& operator=(const RenderComp& other) = delete;
		RenderComp& operator=(RenderComp&& other)	noexcept = delete;

		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		//void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		void Render() const override;

		void LoadImageTexture(const TextureEntry& entry);
		void LoadTextTexture(Texture2D* text);
		void UnloadTexture();

		RenderKey Lock();	//safety feature to document any overlap of components trying to render their texture
		void Unlock(RenderKey key);

		void SetSrcRect(Rect srcRect);
		void SetRenderSize(glm::ivec2 size);	//change the render width and height, will be reset on texture or srcRect change
		void SetHorizontalAlignment(HorizontalAlignment alignment);
		void SetVerticalAlignment(VerticalAlignment alignment);
		void SetHorizontalFlip(bool flip);
		void SetVerticalFlip(bool flip);
		void SetAngle(texture_angle angle);

	private:

		bool CheckLock();
		Texture2D* GetTexture() const;
		void CalculateAlignmentOffset();
		void ApplyFlip();
		void ApplyAngle();

		//=====================================
		ReqComp<TransformComp> m_TransformComp{};
		IRenderSystem* m_pRenderSystem{ &ServiceLocator::GetRenderSystem() };

		std::variant<
			Texture2D*,		//text (and default init to nullptr)
			TextureToken	//image
		> m_TextureData{ nullptr };

		bool m_IsLocked{ false };
		RenderKey m_SavedKey{};	//saves this pointer when Lock() is called

		Rect m_SrcRect{};
		glm::ivec2 m_RenderSize{};

		HorizontalAlignment m_HorizontalAlignment{ HorizontalAlignment::left };
		VerticalAlignment m_VerticalAlignment{ VerticalAlignment::bottom };
		glm::vec2 m_AlignmentOffset{ 0.f, 0.f };

		Flip m_Flip{};
		texture_angle m_Angle{};
	};
}
 
#endif // RENDERCOMP_H