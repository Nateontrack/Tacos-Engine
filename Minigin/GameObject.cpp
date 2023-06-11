#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"

namespace dae
{
	//scene should have 1 gameobject that is the root of all others
	GameObject::GameObject(const glm::vec2& pos)
		:m_WorldPosition{ pos },
		m_PositionIsDirty{ false },
		m_DeletionMark{false},
		m_IsActive{true}
	{}

	GameObject::~GameObject()
	{
		for (auto& component : m_Components)
		{
			component.reset();
		}
		m_Components.clear();
	}

	void GameObject::Update()
	{
		if (m_IsActive)
		{
			for (auto& component : m_Components)
			{
				component->Update();
			}

			for (auto& child : m_Children)
			{
				child->Update();
			}
		}
	}

	void GameObject::Render() const
	{
		if (m_IsActive)
		{
			for (auto& component : m_Components)
			{
				component->Render();
			}

			for (auto& child : m_Children)
			{
				child->Render();
			}
		}
	}

	GameObject* GameObject::GetParent() const
	{
		return m_Parent;
	}

	GameObject* GameObject::GetChildAt(size_t index) const
	{
		return m_Children[index].get();
	}

	int GameObject::GetChildCount() const
	{
		return static_cast<int>(m_Children.size());
	}

	void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
	{
		//position setting
		if (pParent == nullptr)
		{
			SetLocalPosition(GetWorldPosition());
		}
		else
		{
			if (keepWorldPosition)
			{
				SetLocalPosition(GetLocalPosition() - pParent->GetWorldPosition());
			}
			SetPositionDirty();
		}

		std::unique_ptr<GameObject> child;


		if (m_Parent)
		{
			for (auto it = m_Parent->m_Children.begin(); it != m_Parent->m_Children.end(); ++it)
			{
				if (it->get() == this) 
				{
					child = std::move(*it);
					m_Parent->m_Children.erase(it);
					break;
				}
			}
		}

		m_Parent = pParent;

		if (m_Parent)
		{
			if (child == nullptr)
			{
				child = std::unique_ptr<GameObject>(this);
			}
			m_Parent->m_Children.emplace_back(std::move(child));
		}

	}

	void GameObject::SetLocalPosition(const glm::vec2& pos)
	{
		m_LocalPosition = pos;
		SetPositionDirty();

		if (!m_Children.empty())
		{
			for (const auto& child : m_Children)
			{
				child->SetPositionDirty();
			}
		}
	}

	void GameObject::SetPositionDirty()
	{
		m_PositionIsDirty = true;
	}

	const glm::vec2& GameObject::GetWorldPosition()
	{
		if (m_PositionIsDirty)
		{
			UpdateWorldPosition();
		}

		return m_WorldPosition;
	}

	void GameObject::UpdateWorldPosition()
	{
		if (m_PositionIsDirty)
		{
			if (m_Parent == nullptr)
			{
				m_WorldPosition = m_LocalPosition;
			}
			else
			{
				m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
			}
		}
		m_PositionIsDirty = false;
	}

	void GameObject::MarkForDeletion()
	{
		m_DeletionMark = true;
	}

	bool GameObject::GetDeletionMark() const
	{
		return m_DeletionMark;
	}

	void GameObject::DeleteMarkedChildrenRecursive()
	{
		if (m_Children.empty()) return; //recursive end

		for (auto& child : m_Children)
		{
			if (child->GetDeletionMark())
			{
				m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
			}
			else
			{
				child->DeleteMarkedChildrenRecursive();
			}
		}
	}

	void GameObject::SetActive(bool isActive)
	{
		m_IsActive = isActive;
	}

	bool GameObject::GetActive()
	{
		return m_IsActive;
	}
}



