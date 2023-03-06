#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	
	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		T* AddComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

			auto component = std::make_unique<T>(this);
			auto rawComponent = component.get();
			m_Components.push_back(std::move(component));
			return rawComponent;

		}
		template <typename T>
		T* GetComponent() const
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
			for (auto& component : m_Components)
			{
				auto cast_component = dynamic_cast<T*>(component.get());
				if (cast_component != nullptr) 
				{
					//if type is the same return the component
					return cast_component;
				}
			}
			//else return nothing
			return nullptr;
		}

		template <typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
			for (auto& component : m_Components)
			{
				if (typeid(T) == typeid(Component))
				{
					component.reset();
					auto iterator = std::find(m_Components.begin(), m_Components.end(), component);
					if (iterator != m_Components.end()) 
					{
						m_Components.erase(iterator);
					}
				}
			}
		}

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
	};
}
