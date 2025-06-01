#include "TileComp.h"

#include "BMGameDefines.h"

bm::TileComp::TileComp(dae::GameObject& parent, TileType type, glm::ivec2 posIndex)
	:Component{parent}
	, m_IndexPos{ posIndex }
	, m_Pos{ static_cast<float>(TILE_SIZE / 2 + TILE_SIZE * posIndex.x), static_cast<float>(TILE_SIZE / 2 + TILE_SIZE * posIndex.y)}
{
	m_TransformComp.Init(GetOwner());
	m_TransformComp->SetLocalPosition(m_Pos);

	m_RenderComp.Init(GetOwner());
	m_RenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	m_RenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
	switch (type)
	{
	case bm::TileType::Ground:
		m_RenderComp->LoadImageTexture(s_GroundTexture);
		break;
	case bm::TileType::Wall:
		m_RenderComp->LoadImageTexture(s_WallTexture);
		break;
	default:
		m_RenderComp->LoadImageTexture(ERROR_TEXTURE);
		break;
	}
}

glm::vec2 bm::TileComp::GetPosition()
{
	return m_Pos;
}

glm::ivec2 bm::TileComp::GetIndexPosition()
{
	return m_IndexPos;
}
