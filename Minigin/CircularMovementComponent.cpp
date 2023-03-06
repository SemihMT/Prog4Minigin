#include "CircularMovementComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

CircularMovementComponent::CircularMovementComponent(dae::GameObject* parent):
ComponentBase{parent}
{

}

CircularMovementComponent::CircularMovementComponent(dae::GameObject* parent, int radius, int speed , const glm::vec2& displacement) :
ComponentBase{parent}, m_Radius{radius},m_Speed{speed}, m_Dis{displacement}
{
}

void CircularMovementComponent::Update(float deltaTime)
{
	
	const float x{m_Radius * cosf(m_angle)};
	const float y{m_Radius * sinf(m_angle)}; 

	m_angle += m_Speed * deltaTime;
	glm::vec3 pos{};
	GetParent()->SetLocalPosition(glm::vec3{m_Dis.x + x,m_Dis.y + y,0});
	
}
