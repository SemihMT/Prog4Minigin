#include "ComponentBase.h"
#include "GameObject.h"


dae::ComponentBase::ComponentBase(const dae::GameObject* parent) :
	m_pParent{parent}
{
}

const dae::GameObject* dae::ComponentBase::GetParent() const
{
	return m_pParent;
}


