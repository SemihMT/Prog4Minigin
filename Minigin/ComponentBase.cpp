#include "ComponentBase.h"
#include "GameObject.h"
ComponentBase::ComponentBase(const dae::GameObject* parent) :
	m_pParent{parent}
{
}


