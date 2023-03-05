#pragma once
#include <string>
#include <memory>

namespace dae
{
	class GameObject;


	class ComponentBase
	{
	public:
		ComponentBase(const GameObject* parent);
		virtual ~ComponentBase() = default;

		ComponentBase(const ComponentBase& other) = delete;
		ComponentBase(ComponentBase&& other) = delete;
		ComponentBase& operator=(const ComponentBase& other) = delete;
		ComponentBase& operator=(ComponentBase&& other) = delete;

		virtual void Update(float /*deltaTime*/) {}
		virtual void Render()const {}

	protected:
		const GameObject* GetParent() const;

	private:
		//allowing the components to access their owner gives them the ability to access and communicate with the other components of the gameObject
		const GameObject* m_pParent{ nullptr };
	};
}