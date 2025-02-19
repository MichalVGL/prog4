#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <string>
#include <memory>
#include "Component.h"
#include "Texture2D.h"

//-----------------------------------------------------
// Class Forwards
//-----------------------------------------------------
namespace dae
{
	class Font;
}

class RenderComp;

//-----------------------------------------------------
// TextComp Class									
//-----------------------------------------------------
class TextComp final : public Component
{
public:
	TextComp(dae::GameObject& parent, const std::shared_ptr<dae::Font>& font);				// Constructor
	~TextComp() override;				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	TextComp(const TextComp& other)						= delete;
	TextComp(TextComp&& other) noexcept					= delete;
	TextComp& operator=(const TextComp& other)			= delete;
	TextComp& operator=(TextComp&& other)	noexcept	= delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;

	//void Render() const override;

	void SetText(const std::string& text);
	void SetFont(const std::shared_ptr<dae::Font>& font);

private: 

	RenderComp* m_pRenderComp;

	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_TextTexture;
	bool m_NeedsUpdate;
};

 
