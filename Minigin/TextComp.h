#ifndef TEXTCOMP_H
#define TEXTCOMP_H

#include <string>
#include <memory>
#include "Component.h"
#include "Utils.h"
#include "Texture.h"

namespace dae
{

	class Font;
	class RenderComp;

	class TextComp final : public Component	//Args:
	{
	public:

		TextComp(dae::GameObject& parent);				// Constructor

		TextComp(const TextComp& other) = delete;
		TextComp(TextComp&& other) noexcept = delete;
		TextComp& operator=(const TextComp& other) = delete;
		TextComp& operator=(TextComp&& other)	noexcept = delete;

		void Start() override;
		//void FixedUpdate(float deltaFixedTime) override;
		void Update(float deltaTime) override;
		//void LateUpdate(float deltaTime) override;
		//void Render() const override;
		//--------------------------

		void SetText(const std::string& text);
		void SetTextFunc(std::function<std::string()> func);
		void SetFont(const FontEntry& fontEntry);
		void SetSize(font_size size);
		void SetColor(Color color);

	private:

		ReqComp<RenderComp> m_RenderComp{};

		enum class TextMode
		{
			text,
			textFunc
		};

		std::string m_Text{};
		std::function<std::string()> m_TextFunc{};
		TextMode m_Mode{ TextMode::text };

		FontToken m_FontToken{};
		std::unique_ptr<Texture2D> m_pTextTexture;
		Color m_FgColor{.r = 255u, .g = 255u, .b = 255u, .a = 255u};
		const FontEntry* m_pFontEntry{ nullptr };
		font_size m_FontSize{ 28u };

		bool m_FontNeedsUpdate{ false };
		bool m_NeedsUpdate{ false };
	};

}
 
#endif // TEXTCOMP_H