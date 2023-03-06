#pragma once
#include "ComponentBase.h"
#include <glm/glm.hpp>


class TransformComponent final : public dae::ComponentBase
{
public:
	TransformComponent(dae::GameObject* parent);
	TransformComponent(dae::GameObject* parent, const glm::vec3& position);
	~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	void SetLocalPosition(const glm::vec3& position);
	const glm::vec3& GetLocalPosition() const;

	const glm::vec3& GetWorldPosition() const;
	void SetWorldPosition(const glm::vec3& position);

	void Update(float deltaTime) override;

private:
	glm::vec3 m_LocalPosition;
	glm::vec3 m_WorldPosition;

};
