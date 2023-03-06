#include "TransformComponent.h"

TransformComponent::TransformComponent(dae::GameObject* parent):
ComponentBase{parent},
m_WorldPosition{0,0,0}
{
}

TransformComponent::TransformComponent(dae::GameObject* parent,const glm::vec3& position) :
ComponentBase{parent},
m_WorldPosition{position}
{
}

void TransformComponent::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
}
const glm::vec3& TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& TransformComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}

void TransformComponent::SetWorldPosition(const glm::vec3& position)
{
	m_WorldPosition = position;
}

void TransformComponent::Update(float deltaTime)
{
	m_LocalPosition += glm::vec3{0,0,0} * deltaTime;
}
