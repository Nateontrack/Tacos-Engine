#include "HealthDisplay.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

HealthDisplay::HealthDisplay(GameObject* pOwner)
	:Component(pOwner),
	m_DisplayString{"Health: "}
{
	m_TextComp = std::make_unique<TextComponent>(pOwner);
	m_TextComp->SetText(m_DisplayString);
}

void HealthDisplay::Update()
{
	m_TextComp->Update();
}

void HealthDisplay::OnNotify(int health)
{
	std::string display = m_DisplayString + std::to_string(health);
	m_TextComp->SetText(display);
}

void HealthDisplay::OnSubjectDestroy()
{
	m_DisplayString = "";
}

void HealthDisplay::SetDisplayString(const std::string& str)
{
	m_DisplayString = str;
}