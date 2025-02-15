#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <vector>
#include <glm.hpp>
#include "Component.h"
#include "Texture2D.h"

//-----------------------------------------------------
// RenderComp Class									
//-----------------------------------------------------
class RenderComp final : public Component
{
public:
	RenderComp(dae::GameObject& parent);	// Constructor
	~RenderComp() override;					// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	RenderComp(const RenderComp& other)					= default;
	RenderComp(RenderComp&& other) noexcept				= default;
	RenderComp& operator=(const RenderComp& other)		= default;
	RenderComp& operator=(RenderComp&& other)	noexcept	= default;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------

	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;

	void Render() const override;

	std::shared_ptr<dae::Texture2D> LoadTexture(SDL_Texture* texture);
	std::shared_ptr<dae::Texture2D> LoadTexture(const std::string& filename);

	bool UnloadTexture(const std::shared_ptr<dae::Texture2D>& texture);

private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	std::vector<std::shared_ptr<dae::Texture2D>> m_Textures;

};

 
