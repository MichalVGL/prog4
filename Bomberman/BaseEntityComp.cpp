#include "BaseEntityComp.h"

#include "EntityStates.h"
#include "BMGameDefines.h"

bm::BaseEntityComp::BaseEntityComp(dae::GameObject& parent, const EntityStats& entityStats, std::unique_ptr<EntityController>&& controller)
	:Component(parent)
	, m_pController{std::move(controller)}
	, m_pCurrentState{std::make_unique<IdleState>(parent)}
	, m_EntityStats{ entityStats }
{
	//check the controller
	if (!m_pController)
	{
		std::cout << std::format("Error: EntityComp initialized without a valid controller. [{}]\n", GetOwner().GetName());
		throw std::runtime_error("BaseEntityComp: No controller given");
	}

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
#ifdef _DEBUG
	m_pCurrentState->ValidateSprite();
#endif // _DEBUG

	m_SpriteComp->SetSpriteEntry(SPRITEID_MOVEDOWN);
	m_pCurrentState->OnEnter();
}

void bm::BaseEntityComp::Update(float deltaTime)
{
	m_pController->Update(m_EntityCondition);

	UpdateState(deltaTime);
	m_EntityCondition.position = m_TransformComp->GetLocalPosition();
}

void bm::BaseEntityComp::Kill()	//base behaviour
{
	GetOwner().FlagForDeletion();
}

void bm::BaseEntityComp::UpdateState(float deltaTime)
{
	auto pNewState{ m_pCurrentState->Update(deltaTime, m_EntityStats) };
	if (!pNewState)
	{
		pNewState = m_pCurrentState->HandleInput(m_pController->GetInputRef());
	}
	if (pNewState)
	{
		m_pCurrentState->OnExit();	//call exit on the current state
		m_pCurrentState = std::move(pNewState);
		m_pCurrentState->OnEnter();

		m_EntityCondition.stateChanged = true;
		m_EntityCondition.stateType = m_pCurrentState->GetStateType();
	}
	else
	{
		m_EntityCondition.stateChanged = false;
	}
}