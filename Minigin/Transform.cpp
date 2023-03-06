#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"

namespace dae
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		:Component(pOwner),
		m_Position{ 0,0,0 },
		m_NeedsUpdate{true}
	{}

	void TransformComponent::Update()
	{
		if (m_NeedsUpdate)
		{
			GetOwner()->GetComponent<RenderComponent>()->SetTransform(m_Position);
			m_NeedsUpdate = false;
		}
	}

	void TransformComponent::SetPosition(const float x, const float y, const float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
		m_NeedsUpdate = true;
	}
}


