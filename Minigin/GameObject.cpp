#include <string>
#include "GameObject.h"

#include <ranges>
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject() :
	m_Components{}
{
}

dae::GameObject::~GameObject()
{
	for (auto& pair : m_Components) {
		delete pair.second;
	}
	m_Components.clear();
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

