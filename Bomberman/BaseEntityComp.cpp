#include "BaseEntityComp.h"

#include "EntityStates.h"
#include "BMGameDefines.h"

bm::BaseEntityComp::BaseEntityComp(dae::GameObject& parent, const EntityStats& entityStats)
	:Component(parent)
	, m_pCurrentState{std::make_unique<IdleState>(parent)}
	, m_EntityStats{ entityStats }
{
	//make sure spritecomp is added before this comp!!!
	m_TransformComp.Init(GetOwner());
	m_SpriteComp.Init(GetOwner());
	m_SpriteComp->SetFPS(8.f);	//todo, use the defines
	
	//Align to center 
	auto* pRenderComp = GetOwner().GetComponent<dae::RenderComp>();
	pRenderComp->SetHorizontalAlignment(dae::HorizontalAlignment::center);
	pRenderComp->SetVerticalAlignment(dae::VerticalAlignment::center);
}


bm::BaseEntityComp::~BaseEntityComp() = default;

void bm::BaseEntityComp::Start()
{
	m_SpriteComp->SetSpriteEntry(SPRITEID_MOVEDOWN);
	m_pCurrentState->OnEnter();
}

void bm::BaseEntityComp::Kill()	//base behaviour
{
	GetOwner().FlagForDeletion();
}

bool bm::BaseEntityComp::UpdateState(float deltaTime)
{
	auto pNewState{ m_pCurrentState->Update(deltaTime, m_EntityStats) };
	if (!pNewState)
	{
		pNewState = m_pCurrentState->HandleInput(m_EntityInput);
	}
	if (pNewState)
	{
		m_pCurrentState->OnExit();	//call exit on the current state
		m_pCurrentState = std::move(pNewState);
		m_pCurrentState->OnEnter();
		return true;	//state has been changed
	}
	return false;
}