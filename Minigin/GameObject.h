#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		GameObject(const glm::vec2& pos);
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

		GameObject* GetParent() const;
		GameObject* GetChildAt(size_t idx) const;
		bool GetDeletionMark() const;
		int GetChildCount() const;
		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec2& GetWorldPosition();
		bool GetActive();
		
		
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		void MarkForDeletion();
		void DeleteMarkedChildrenRecursive();
		void SetLocalPosition(const glm::vec2& pos);
		void SetPositionDirty();
		void SetActive(bool isActive);

	private:
		void UpdateWorldPosition();

		std::vector<std::unique_ptr<Component>> m_Components;
		std::vector<std::unique_ptr<GameObject>> m_Children{};
		GameObject* m_Parent{};

		glm::vec2 m_WorldPosition;
		glm::vec2 m_LocalPosition;
		bool m_PositionIsDirty;
		bool m_DeletionMark;
		bool m_IsActive;
	};
}
