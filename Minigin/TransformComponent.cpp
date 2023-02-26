#include "TransformComponent.h"

TransformComponent::TransformComponent(const dae::GameObject* parent):
ComponentBase{parent},
m_position{0,0,0}
{
}

TransformComponent::TransformComponent(const dae::GameObject* parent,const glm::vec3 position) :
ComponentBase{parent},
m_position{position}
{
}

void TransformComponent::SetPosition(const glm::vec3 position)
{
	m_position = position;
}

glm::vec3 TransformComponent::GetPosition() const
{
	return m_position;
}

void TransformComponent::Update(float deltaTime)
{
	m_position += glm::vec3{0,0,0} * deltaTime;
}
