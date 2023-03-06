#pragma once
#include <glm/vec2.hpp>

#include "ComponentBase.h"

class CircularMovementComponent final : public dae::ComponentBase
{
public:
	CircularMovementComponent(dae::GameObject* parent);
	CircularMovementComponent(dae::GameObject* parent, int radius, int speed,const glm::vec2& displacement = {0,0});

	~CircularMovementComponent() = default;

	CircularMovementComponent(const CircularMovementComponent& other) = delete;
	CircularMovementComponent(CircularMovementComponent&& other) = delete;
	CircularMovementComponent& operator=(const CircularMovementComponent& other) = delete;
	CircularMovementComponent& operator=(CircularMovementComponent&& other) = delete;

	void Update(float deltaTime) override;

private:
	int m_Radius;
	int m_Speed;
	glm::vec2 m_Dis;
	float m_angle;
};
