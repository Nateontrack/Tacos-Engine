#include "OrbitComponent.h"
#include "GameObject.h"
#include "Timer.h"


namespace dae
{
	OrbitComponent::OrbitComponent(GameObject* pOwner)
		:Component(pOwner),
		m_Radius{30.f},
		m_RotationSpeed{3.f},
		m_RotatesClockwise{false},
		m_Angle{},
		m_IsRotating{true}
	{}

	void OrbitComponent::Update()
	{
		if (m_IsRotating)
		{
			float elapsedTime = Timer::GetInstance()->GetElapsedSec();
			if (m_RotatesClockwise)
			{
				m_Angle -= elapsedTime * m_RotationSpeed;
			}
			else
			{
				m_Angle += elapsedTime * m_RotationSpeed;
			}

			glm::vec3 rotationOffset{m_Radius * cosf(m_Angle), m_Radius * sinf(m_Angle), 0};

			GetOwner()->SetLocalPosition(rotationOffset);
		}
	}
}