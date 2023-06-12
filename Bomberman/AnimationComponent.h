#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class RenderComponent;

	class AnimationComponent final : public Component
	{
	public:
		AnimationComponent(GameObject* pOwner, const glm::vec2& firstPos, int nrFrames, float width, float height, float sizeFactor = 1.f, bool isRepeating = false, int repeatFrame = 0);
		AnimationComponent(GameObject* pOwner, const glm::vec2& firstPos, int nrFrames, float width, float height, float frameTime, float sizeFactor = 1.f, bool isRepeating = false, int repeatFrame = 0);

		
		virtual void Update() override;
		virtual void Render() const override {};

		void Reset();
		void SetPaused(bool pause);
		float GetAnimTime();

		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;
		virtual ~AnimationComponent() = default;
	private:
		const int m_NrFrames;
		const int m_RepeatFrame;
		const float m_FrameWidth;
		const float m_FrameHeight;
		const float m_FrameTime;
		const float m_SizeFactor;
		const bool m_IsRepeating;
		const glm::vec2 m_FirstPos;

		glm::vec2 m_CurrentPos;

		float m_AccumulatedTime;
		int m_CurrentFrame;
		bool m_Paused;

		RenderComponent* m_RenderComponent;
	};
}

