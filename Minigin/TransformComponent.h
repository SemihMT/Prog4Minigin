#pragma once
#include "ComponentBase.h"
#include <glm/glm.hpp>


class TransformComponent final : public ComponentBase
{
public:
	TransformComponent(const dae::GameObject* parent);
	TransformComponent(const dae::GameObject* parent, const glm::vec3 position);
	~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	void SetPosition(const glm::vec3 position);
	glm::vec3 GetPosition() const;
	void Update(float deltaTime) override;

private:
	glm::vec3 m_position;
};
