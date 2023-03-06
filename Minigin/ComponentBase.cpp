#include "ComponentBase.h"
#include "GameObject.h"

dae::ComponentBase::ComponentBase(dae::GameObject* parent) :
	m_pParent{parent}
{
}

dae::GameObject* dae::ComponentBase::GetParent() const
{
	return m_pParent;
}


