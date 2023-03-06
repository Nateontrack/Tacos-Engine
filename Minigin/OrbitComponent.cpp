#include "OrbitComponent.h"
#include "GameObject.h"
#include "Time.h"


namespace dae
{
	OrbitComponent::OrbitComponent(GameObject* pOwner)
		:Component(pOwner),
		m_Radius{30.f},
		m_RotationSpeed{3.f},
		m_RotatesClockwise{false},
		m_Angle{},
		m_Center{},
		m_HasParentFlag{},
		m_IsRotating{true}
	{
		if (GetOwner()->GetParent() == nullptr)
		{
			m_Center = GetOwner()->GetWorldPosition();
			m_HasParentFlag = false;
		}
		m_HasParentFlag = true;
	}

	bool OrbitComponent::CheckForParent() const
	{
		return (GetOwner()->GetParent() != nullptr);
	}

	void OrbitComponent::Update()
	{
		if (m_IsRotating)
		{
			float elapsedTime = Time::GetInstance()->GetElapsedSec();
			if (m_RotatesClockwise)
			{
				m_Angle -= elapsedTime * m_RotationSpeed;
			}
			else
			{
				m_Angle += elapsedTime * m_RotationSpeed;
			}
			
			//parent functionality switching
			if (m_HasParentFlag != CheckForParent())
			{
				if (m_HasParentFlag)
				{
					m_Center = GetOwner()->GetWorldPosition();
					m_HasParentFlag = false;
				}
				else
				{
					m_HasParentFlag = true;
				}
			}

			glm::vec3 rotationOffset{m_Radius * cosf(m_Angle), m_Radius * sinf(m_Angle), 0};

			if (m_HasParentFlag)
			{
				GetOwner()->SetLocalPosition(rotationOffset);
			}
			else
			{
				GetOwner()->SetLocalPosition(m_Center + rotationOffset);
			}
		}
	}
}