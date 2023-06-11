#include "ScoreDisplay.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

ScoreDisplay::ScoreDisplay(GameObject* pOwner)
	:Component(pOwner),
	m_DisplayString{"Score: "}
{
	m_TextComp = std::make_unique<TextComponent>(pOwner);

}

void ScoreDisplay::Update()
{
	m_TextComp->Update();
}

void ScoreDisplay::OnNotify(int score)
{
	std::string display = m_DisplayString + std::to_string(score);
	m_TextComp->SetText(display);
}

void ScoreDisplay::OnSubjectDestroy()
{}

void ScoreDisplay::SetDisplayString(const std::string& str)
{
	m_DisplayString = str;
}