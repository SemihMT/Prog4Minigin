#include <string>
#include "GameObject.h"

#include <ranges>
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject() :
	m_Components{}, m_pParentObject{ nullptr }, m_pChildren{}, m_PositionFlag{ false }
{
}

dae::GameObject::~GameObject()
{
	for (auto& pair : m_Components) {
		delete pair.second;
	}
	m_Components.clear();


}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	//No parent: local pos = world pos
	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPos)
		{
			SetLocalPosition(GetLocalPosition() - m_pParentObject->GetWorldPosition());
		}
		SetPositionDirty();
	}
	if (m_pParentObject)
	{
		m_pParentObject->RemoveChild(this);
	}
	m_pParentObject = parent;
	if (m_pParentObject)
	{
		m_pParentObject->AddChild(this);
	}

}

dae::GameObject* dae::GameObject::GetParent()
{
	return m_pParentObject;
}

void dae::GameObject::AddChild(GameObject* child)
{
	//check if child has already been added or not
	if (std::count(m_pChildren.begin(), m_pChildren.end(), child))
	{
		return;
	}
	m_pChildren.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (auto it = std::find(m_pChildren.begin(), m_pChildren.end(), child) != m_pChildren.end()) {
		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
	}
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionFlag = true;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	GetComponent<TransformComponent>()->SetLocalPosition(pos);
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return GetComponent<TransformComponent>()->GetLocalPosition();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionFlag)
	{
		UpdateWorldPosition();
	}
	return GetComponent<TransformComponent>()->GetWorldPosition();
}

void dae::GameObject::UpdateWorldPosition()
{
	const auto localPos = GetComponent<TransformComponent>()->GetLocalPosition();

	if (m_PositionFlag)
	{
		if (m_pParentObject == nullptr)
		{
			GetComponent<TransformComponent>()->SetWorldPosition(localPos);
		}
		else
		{
			const auto parentWorldPos = m_pParentObject->GetComponent<TransformComponent>()->GetWorldPosition();
			GetComponent<TransformComponent>()->SetWorldPosition(parentWorldPos + localPos);
		}
	}
	m_PositionFlag = false;
}

void dae::GameObject::Update(float dt)
{
	//update all components
	for (auto& pair : m_Components) {
		pair.second->Update(dt);
	}
}

void dae::GameObject::Render() const
{
	for (auto& pair : m_Components) {
		pair.second->Render();

	}
}

void dae::GameObject::RenderUI() const
{
	for (auto& pair : m_Components) {
		pair.second->RenderUI();

	}
}

