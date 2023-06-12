#include "GameCommands.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerController.h"

using namespace dae;

void MoveCommand::Execute()
{
	glm::vec2 movement{m_Direction* m_Speed* Timer::GetInstance()->GetElapsedSec()};
	
	GetGameObject()->GetComponent<PlayerController>()->AddMovement(movement);
}

void DamageCommand::Execute()
{
	GetGameObject()->GetComponent<PlayerController>()->SetState(PlayerController::PlayerState::die);
}

void ScoreCommand::Execute()
{
	GetGameObject()->GetComponent<PlayerController>()->ScorePoints();
}