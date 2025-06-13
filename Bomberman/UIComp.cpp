#include "UIComp.h"

bm::UIComp::UIComp(dae::GameObject& parent)
	:dae::Component(parent)
{
	m_RenderComp.Init(parent);
	m_RenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	m_RenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);

	m_TextComp.Init(parent);
}

void bm::UIComp::Select()
{
	m_TextComp->SetColor(s_SelectedColor);
}

void bm::UIComp::UnSelect()
{
	m_TextComp->SetColor(s_NormalColor);
}

glm::vec2 bm::UIComp::GetTextureSize() const
{
	return m_RenderComp->GetTextureSize();
}
