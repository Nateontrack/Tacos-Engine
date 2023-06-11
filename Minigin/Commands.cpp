#include "Commands.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerController.h"

using namespace dae;

void MoveCommand::Execute()
{
	GameObject* object{ GetGameObject() };

	glm::vec2 currentPos{object->GetLocalPosition()};
	glm::vec2 movement{m_Direction * m_Speed * Timer::GetInstance()->GetElapsedSec()};
	object->SetLocalPosition(currentPos + movement);
}

void DamageCommand::Execute()
{
	GetGameObject()->GetComponent<PlayerController>()->Die();
}

void ScoreCommand::Execute()
{
	GetGameObject()->GetComponent<PlayerController>()->ScorePoints();
}