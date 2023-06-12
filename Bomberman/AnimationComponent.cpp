#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "Timer.h"
#include "GameObject.h"


using namespace dae;

AnimationComponent::AnimationComponent(GameObject* pOwner, const glm::vec2& firstPos, int nrFrames, float width, float height, float sizeFactor, bool isRepeating, int repeatFrame)
	:Component(pOwner),
	m_FirstPos{ firstPos },
	m_NrFrames{ nrFrames },
	m_FrameWidth{ width },
	m_FrameHeight{ height },
	m_IsRepeating{ isRepeating },
	m_RepeatFrame{ repeatFrame },
	m_FrameTime{ 0.083333f },
	m_CurrentFrame{ 0 },
	m_AccumulatedTime{},
	m_SizeFactor{ sizeFactor },
	m_Paused{false}
{
	m_CurrentPos.x = m_FirstPos.x;
	m_CurrentPos.y = m_FirstPos.y;
	m_RenderComponent = GetOwner()->GetComponent<RenderComponent>();
}

AnimationComponent::AnimationComponent(GameObject* pOwner, const glm::vec2& firstPos, int nrFrames, float width, float height, float frameTime, float sizeFactor, bool isRepeating, int repeatFrame)
	:Component(pOwner),
	m_FirstPos{ firstPos },
	m_NrFrames{ nrFrames },
	m_FrameWidth{ width },
	m_FrameHeight{ height },
	m_IsRepeating{ isRepeating },
	m_RepeatFrame{ repeatFrame },
	m_FrameTime{ frameTime },
	m_CurrentFrame{ 0 },
	m_AccumulatedTime{},
	m_SizeFactor{sizeFactor},
	m_Paused{ false }
{
	m_CurrentPos.x = m_FirstPos.x;
	m_CurrentPos.y = m_FirstPos.y;
	m_RenderComponent = GetOwner()->GetComponent<RenderComponent>();
}

void AnimationComponent::Update()
{
	if (!m_Paused)
	{
		m_AccumulatedTime += Timer::GetInstance()->GetElapsedSec();
		if (m_AccumulatedTime > m_FrameTime)
		{
			m_CurrentFrame++;
			m_AccumulatedTime -= m_FrameTime;

			if (m_IsRepeating)
			{
				if (m_CurrentFrame >= m_RepeatFrame)
				{
					m_CurrentFrame %= m_NrFrames - m_RepeatFrame;
					m_CurrentFrame += m_RepeatFrame;
				}

			}
			else if (m_CurrentFrame == m_NrFrames)
			{
				m_CurrentFrame--;
			}

			m_CurrentPos.x = m_FirstPos.x + m_FrameWidth * m_CurrentFrame;
			
		}
	}
	m_RenderComponent->SetSource(m_CurrentPos, m_FrameWidth, m_FrameHeight, m_SizeFactor);
}

void AnimationComponent::SetPaused(bool paused)
{
	m_Paused = paused;
}

void AnimationComponent::Reset()
{
	m_CurrentFrame = 0;
	m_AccumulatedTime = 0;
	m_CurrentPos.x = m_FirstPos.x;
	m_Paused = false;
}

float AnimationComponent::GetAnimTime()
{
	return m_FrameTime * m_NrFrames;
}