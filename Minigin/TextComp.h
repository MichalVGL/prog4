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
	TextComp(const TextComp& other)					= default;
	TextComp(TextComp&& other) noexcept				= default;
	TextComp& operator=(const TextComp& other)		= default;
	TextComp& operator=(TextComp&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	//void FixedUpdate(float deltaFixedTime) override;
	void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;

	//void Render() const override;	//unused

	void SetText(const std::string& text);
	void SetFont(const std::shared_ptr<dae::Font>& font);

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_TextTexture;
	bool m_NeedsUpdate;
};

 
