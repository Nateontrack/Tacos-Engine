#include <string>
#include "Component.h"
#include "Time.h"
#include "GameObject.h"

#include "HealthComponent.h"

using namespace dae;

HealthComponent::HealthComponent(GameObject* pOwner)
	:Component(pOwner),
	m_MaxHealth{5},
	m_CurrentHealth{5}
{}

void HealthComponent::Update()
{

}

int HealthComponent::GetHealth() const
{
	return m_CurrentHealth;
}

void HealthComponent::Die()
{
	if (m_CurrentHealth > 1)
	{
		m_CurrentHealth--;
		m_PlayerDied.Notify(m_CurrentHealth);
		GetOwner()->SetLocalPosition(glm::vec2{});
	}
	else
	{
		m_CurrentHealth = 0;
		m_PlayerDied.Notify(m_CurrentHealth);
		GetOwner()->SetActive(false);
	}
}

void HealthComponent::GainLife()
{
	if (m_CurrentHealth < m_MaxHealth)
	{
		m_CurrentHealth++;
	}
}

void HealthComponent::SetObserver(Observer<int>* hud)
{
	m_PlayerDied.AddObserver(hud);
	m_PlayerDied.Notify(m_CurrentHealth);
}

void HealthComponent::SetMaxHealth(int health)
{
	m_MaxHealth = health;
	m_CurrentHealth = health;
	m_PlayerDied.Notify(m_CurrentHealth);
}