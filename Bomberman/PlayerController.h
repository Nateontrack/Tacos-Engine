#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent;
	class HealthComponent;

	class PlayerController final : public Component
	{
	public:
		PlayerController(GameObject* pOwner);

		virtual ~PlayerController();

		virtual void Update() override {};
		virtual void Render() const override {};

		// Mark copy/move constructors and assignment operators as deleted
		PlayerController(const PlayerController& other) = delete;
		PlayerController(PlayerController&& other) = delete;
		PlayerController& operator=(const PlayerController& other) = delete;
		PlayerController& operator=(PlayerController&& other) = delete;

		void ScorePoints();
		void Die();
		void SetObserver(Observer<int>* hud);
		void SetKeyboard();

	private:
		void Init();

		static int s_InstanceCount; // Static member variable to keep track of instance count
		const int m_MaxInstanceCount;
		int m_PlayerIndex;

		const float m_Speed;

		std::unique_ptr<ScoreComponent> m_ScoreComp;
		std::unique_ptr<HealthComponent> m_HealthComp;
	};
}



