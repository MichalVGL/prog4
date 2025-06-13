#include "ExecutingUIComp.h"

bm::ExecutingUIComp::ExecutingUIComp(dae::GameObject& parent, std::unique_ptr<dae::Command>&& command)
	:UIComp(parent)
	, m_pCommand(std::move(command))
{
}

void bm::ExecutingUIComp::PrimaryInteract()
{
	if (m_pCommand)
	{
		m_pCommand->Execute();
	}
}