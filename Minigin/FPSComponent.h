#pragma once
#include <cmath>
#include "Component.h"
#include "TextComponent.h"
#include "Time.h"


namespace dae
{
	class GameObject;
	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* pOwner)
			:Component(pOwner)
		{}
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update() override
		{
			float FPS = 1 / Time::GetInstance()->GetElapsedSec();
			m_CurrentFPS = static_cast<int>(round(FPS));

			std::string strFPS{ "FPS: " };
			strFPS += std::to_string(m_CurrentFPS);

			GetOwner()->GetComponent<TextComponent>()->SetText(strFPS);
		}
		virtual void Render() const override {}

		int GetFPS() const
		{
			return m_CurrentFPS;
		}
	private:
		int m_CurrentFPS{};
	};
}


