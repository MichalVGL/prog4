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
	, m_Textures{}
{
	// nothing to create
}

RenderComp::~RenderComp()
{
	// nothing to destroy
}

void RenderComp::Render() const
{
	glm::vec2 pos{};

	auto tComp = m_GObjectParent.GetComponent<TransformComp>();
	if (tComp.get() != nullptr)
	{
		pos += tComp->GetPosition();
	}

	for (auto& text : m_Textures)
	{
		dae::Renderer::GetInstance().RenderTexture(*text, pos.x, pos.y);
	}
}

std::shared_ptr<dae::Texture2D> RenderComp::LoadTexture(SDL_Texture* texture)
{
	m_Textures.push_back(std::make_shared<dae::Texture2D>(texture));

	return m_Textures.back();
}

std::shared_ptr<dae::Texture2D> RenderComp::LoadTexture(const std::string& filename)
{
	m_Textures.push_back(dae::ResourceManager::GetInstance().LoadTexture(filename));

	return m_Textures.back();
}

bool RenderComp::UnloadTexture(const std::shared_ptr<dae::Texture2D>& texture)
{
	auto loc = std::find_if(m_Textures.begin(), m_Textures.end(), [texture](const std::shared_ptr<dae::Texture2D>& x) {
		return x.get() == texture.get();
		});

	if (loc != m_Textures.end())
	{
		m_Textures.erase(loc);
		return true;
	}
	else
	{
		return false;
	}
}




