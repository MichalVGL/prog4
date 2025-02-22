//---------------------------
// Include Files
//---------------------------
#include "RenderComp.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TransformComp.h"

//---------------------------
// Constructor & Destructor
//---------------------------
RenderComp::RenderComp(dae::GameObject& parent)
	:Component{ parent }
	, m_pTransformComp{}
	, m_Texture_sPtr{}
{
	// nothing to create
}

void RenderComp::Start()
{
	m_pTransformComp = GetOwnerComponent<TransformComp>();
}

void RenderComp::Render() const
{
	glm::vec2 pos{GetOwner().GetWorldPos()};

	if (m_Texture_sPtr.get() != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture_sPtr, pos.x, pos.y);
	}
}

std::shared_ptr<dae::Texture2D> RenderComp::LoadTexture(SDL_Texture* texture)
{
	m_Texture_sPtr = std::make_shared<dae::Texture2D>(texture);

	return m_Texture_sPtr;
}

std::shared_ptr<dae::Texture2D> RenderComp::LoadTexture(const std::string& filename)
{
	m_Texture_sPtr = dae::ResourceManager::GetInstance().LoadTexture(filename);

	return m_Texture_sPtr;
}

void RenderComp::UnloadTexture()	//not tested
{
	m_Texture_sPtr.reset();
}




