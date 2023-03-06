#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"

namespace dae
{
	GameObject::GameObject(const glm::vec3& pos)
		:m_WorldPosition{ pos },
		m_PositionIsDirty {false}
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
		for (auto& component : m_Components) 
		{
			component->Update();
		}
	}

	void GameObject::Render() const
	{
		for (auto& component : m_Components)
		{
			component->Render();
		}
	}

	GameObject* GameObject::GetParent() const
	{
		return m_Parent;
	}

	GameObject* GameObject::GetChildAt(size_t index) const
	{
		return m_Children[index];
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

		if (m_Parent)
		{
			//remove from previous parent
			m_Parent->RemoveChild(this);
		}
		//set new parent
		m_Parent = pParent;
		if (m_Parent)
		{
			//if has a parent add this to the children of the parent
			m_Parent->AddChild(this);
		}
	}

	void GameObject::AddChild(GameObject* pChild)
	{
		m_Children.push_back(pChild);
	}

	void GameObject::RemoveChild(GameObject* pChild)
	{
		pChild->SetParent(nullptr, true);

		auto iterator = std::find(m_Children.begin(), m_Children.end(), pChild);
		if (iterator != m_Children.end())
		{
			m_Children.erase(iterator);
		}
	}

	void GameObject::SetLocalPosition(const glm::vec3& pos)
	{
		m_LocalPosition = pos;
		SetPositionDirty();
	}

	void GameObject::SetPositionDirty()
	{
		m_PositionIsDirty = true;
	}

	const glm::vec3& GameObject::GetWorldPosition()
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
}

