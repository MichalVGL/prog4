#ifndef RENDERCOMP_H
#define RENDERCOMP_H

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <vector>
#include <glm.hpp>
#include "Component.h"
#include "Texture2D.h"

class TransformComp;

//-----------------------------------------------------
// RenderComp Class									
//-----------------------------------------------------
class RenderComp final : public Component
{
public:
	RenderComp(dae::GameObject& parent);

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	RenderComp(const RenderComp& other)						= delete;
	RenderComp(RenderComp&& other) noexcept					= delete;
	RenderComp& operator=(const RenderComp& other)			= delete;
	RenderComp& operator=(RenderComp&& other)	noexcept	= delete;

	//-------------------------------------------------
	// Base functions						
	//-------------------------------------------------

	void Start() override;

	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;

	void Render() const override;

	std::shared_ptr<dae::Texture2D> LoadTexture(SDL_Texture* texture);
	std::shared_ptr<dae::Texture2D> LoadTexture(const std::string& filename);

	void UnloadTexture();

private: 

	TransformComp* m_pTransformComp;

	std::shared_ptr<dae::Texture2D> m_Texture_sPtr;

};

 
#endif // RENDERCOMP_H