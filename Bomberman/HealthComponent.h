#pragma once
#include "Observer.h"


namespace dae
{
	class Component;
	class GameObject;
	

	class HealthComponent final : public Component
	{
	public:
		HealthComponent(GameObject* pOwner);

		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update() override;

		virtual void Render() const override {}

		void Die();
		void GainLife();
		int GetHealth() const;

		void SetObserver(Observer<int>* hud);
		void SetMaxHealth(int health);
		
	private:
		int m_MaxHealth;
		int m_CurrentHealth;

		Subject<int> m_PlayerDied;
	};
}



