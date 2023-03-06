#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <glm/vec3.hpp>

#include "ComponentBase.h"
namespace dae
{
	class GameObject final
	{
	public:
		void Update(float dt);
		void Render() const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T, class... Args> T* AddComponent(Args&&... args);
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		void SetParent(GameObject* parent, bool keepWorldPos);
		dae::GameObject* GetParent();
		const glm::vec3& GetWorldPosition();

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;

	private:

		//store all components
		std::unordered_map<std::type_index, ComponentBase*> m_Components;

		//store children
		std::vector<GameObject*> m_pChildren;

		//editing the vector
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);


		//This GameObject's parent, if it has one.
		GameObject* m_pParentObject = nullptr;

		//Dirty flag for the position
		bool m_PositionFlag;

		void SetPositionDirty();

		void UpdateWorldPosition();

		
		
	};

	//the args stuff is used to forward the arguments to the correct constructor
	template <typename T, class... Args>
	T* dae::GameObject::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<ComponentBase, T>::value, "Component must derive from ComponentBase");
		//Add a new element to the unordered map
		T* cpt = new T(this, std::forward<Args>(args)... );
		m_Components[typeid(T)] = cpt;
		return cpt;
	}

	template <typename T>
	T* dae::GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<ComponentBase, T>::value, "Component must derive from ComponentBase");
		auto it = m_Components.find(typeid(T));
		if (it != m_Components.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}

	template <typename T>
	void dae::GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<ComponentBase, T>::value, "Component must derive from ComponentBase");
		auto it = m_Components.find(std::type_index(typeid(T)));
        if (it != m_Components.end()) {
            delete it->second;
            m_Components.erase(it);
		}
	}
}
