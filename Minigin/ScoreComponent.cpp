#include <string>
#include "Component.h"
#include "Time.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include "InputManager.h"

using namespace dae;

ScoreComponent::ScoreComponent(GameObject* pOwner, int playerIndex)
	:Component(pOwner),
	m_Increment{ 25 },
	m_CurrentScore{ 0 },
	m_PlayerIndex{playerIndex}
{}

void ScoreComponent::Update()
{

}

int ScoreComponent::GetScore() const
{
	return m_CurrentScore;
}

void ScoreComponent::Reset()
{
	m_CurrentScore = 0;
	m_ScorePoints.Notify(m_CurrentScore);
}

void ScoreComponent::GainScore()
{
	m_CurrentScore += m_Increment;
	m_ScorePoints.Notify(m_CurrentScore);
}

void ScoreComponent::SetObserver(Observer<int>* hud)
{
	m_ScorePoints.AddObserver(hud);
	m_ScorePoints.Notify(0);
}

void ScoreComponent::Init()
{

}

