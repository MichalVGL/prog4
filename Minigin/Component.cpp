//---------------------------
// Include Files
//---------------------------
#include "GameObject.h"
#include "Component.h"

//---------------------------
// Constructor & Destructor
//---------------------------
Component::Component(dae::GameObject& parent)
	:m_GObjectParent{parent}
{
}

Component::~Component()
{
	// nothing to destroy
}




