#include <stdexcept>
#include <SDL.h>
#include "GameObject.h"
#include "PlayerController.h"
#include "InputManager.h"
#include "XboxController.h"
#include "GameCommands.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "HealthDisplay.h"
#include "ScoreDisplay.h"

#include "Timer.h"


using namespace dae;

int PlayerController::s_InstanceCount = 0;

PlayerController::PlayerController(GameObject* pOwner)
	: Component(pOwner),
	m_MaxInstanceCount{ 4 },
	m_Speed{200.f},
	m_DeathTimer{0.f},
	m_State{PlayerState::idle}
{
	// Increment the instance count when a new PlayerController is created
	++s_InstanceCount;
	m_PlayerIndex = s_InstanceCount - 1;


	if (s_InstanceCount > 4)
	{
		// Throw an exception or handle the error as per your requirements
		throw std::runtime_error("Only four instances of PlayerController are allowed.");
	}
	InitCommands();


	m_ScoreComp = std::make_unique<ScoreComponent>(pOwner, m_PlayerIndex);
	m_HealthComp = std::make_unique<HealthComponent>(pOwner);
	m_AnimationSheet = std::make_unique<AnimationSheetComponent>(pOwner);
	m_AnimationSheet->CreateAnimationsFromFile("../Data/LoadingData/PlayerAnimations.xml");

	m_StateChanged = std::make_unique<Subject<int>>();
	m_StateChanged->AddObserver(dynamic_cast<Observer<int>*>(m_AnimationSheet.get()));
	m_StateChanged->Notify(static_cast<int>(m_State));
}

void PlayerController::SetState(PlayerState state)
{
	if ((state == PlayerState::die) && (m_State != PlayerState::die))
	{
		m_State = state;
		m_StateChanged->Notify(static_cast<int>(m_State));
	}
}

void PlayerController::Die()
{
	if (GetOwner()->GetActive())
	{
		m_HealthComp->Die();
	}
}

void PlayerController::ScorePoints()
{
	if (GetOwner()->GetActive())
	{
		m_ScoreComp->GainScore();
	}
}

void PlayerController::SetObserver(Observer<int>* hud)
{
	if (dynamic_cast<HealthDisplay*>(hud))
	{
		m_HealthComp->SetObserver(hud);
	}
	if (dynamic_cast<ScoreDisplay*>(hud))
	{
		m_ScoreComp->SetObserver(hud);
	}
}

void PlayerController::Update()
{
	switch (m_State)
	{
	case dae::PlayerController::PlayerState::idle:
	case dae::PlayerController::PlayerState::moveLeft:
	case dae::PlayerController::PlayerState::moveDown:
	case dae::PlayerController::PlayerState::moveRight:
	case dae::PlayerController::PlayerState::moveUp:
		MovementState();
		break;
	case dae::PlayerController::PlayerState::die:
		DieState();
		break;
	default:
		break;
	}

	m_AnimationSheet->Update();

	m_CurrentMovement = glm::vec2{0,0};
}

void PlayerController::MovementState()
{
	PlayerState nextState{};
	if (m_CurrentMovement.x > 0)
	{
		nextState = PlayerState::moveRight;
	}
	else if (m_CurrentMovement.x < 0)
	{
		nextState = PlayerState::moveLeft;
	}
	else if (m_CurrentMovement.y > 0)
	{
		nextState = PlayerState::moveUp;
	}
	else if (m_CurrentMovement.y < 0)
	{
		nextState = PlayerState::moveDown;
	}
	else
	{
		nextState = PlayerState::idle;
		m_AnimationSheet->SetPaused(true);
	}

	
	if (nextState != PlayerState::idle)
	{
		m_AnimationSheet->SetPaused(false);

		if (nextState != m_State)
		{
			m_State = nextState;
			m_StateChanged->Notify(static_cast<int>(m_State));
		}
	}

	GameObject* owner{ GetOwner() };
	glm::vec2 currentPos{owner->GetLocalPosition()};
	owner->SetLocalPosition(currentPos + m_CurrentMovement);
}

void PlayerController::DieState()
{
	m_DeathTimer += Timer::GetInstance()->GetElapsedSec();
	if (m_DeathTimer > m_AnimationSheet->GetAnimationTime(static_cast<int>(PlayerState::die)))
	{
		Die();
		m_DeathTimer = 0.f;
		m_State = PlayerState::moveLeft;
		m_StateChanged->Notify(static_cast<int>(m_State));
	}
}

void PlayerController::AddMovement(const glm::vec2& movement)
{
	m_CurrentMovement += movement;
}

void PlayerController::InitCommands()
{
	GameObject* owner{ GetOwner() };

	std::unique_ptr<dae::Command> moveUp = std::make_unique<dae::MoveCommand>(owner, glm::vec2{0, -1}, m_Speed);
	std::unique_ptr<dae::Command> moveDown = std::make_unique<dae::MoveCommand>(owner, glm::vec2{0, 1}, m_Speed);
	std::unique_ptr<dae::Command> moveRight = std::make_unique<dae::MoveCommand>(owner, glm::vec2{1, 0}, m_Speed);
	std::unique_ptr<dae::Command> moveLeft = std::make_unique<dae::MoveCommand>(owner, glm::vec2{-1, 0}, m_Speed);
	std::unique_ptr<dae::Command> takeDamage = std::make_unique<dae::DamageCommand>(owner);
	std::unique_ptr<dae::Command> score = std::make_unique<dae::ScoreCommand>(owner);

	using Button = XBox360Controller::ControllerButton;
	using ButtonType = InputManager::InputType;

	/*if (s_InstanceCount == 1)
	{
		InputManager::GetInstance().AddCommandKeyboard(std::move(moveUp), SDL_SCANCODE_W, ButtonType::Pressed);
		InputManager::GetInstance().AddCommandKeyboard(std::move(moveDown), SDL_SCANCODE_S, ButtonType::Pressed);
		InputManager::GetInstance().AddCommandKeyboard(std::move(moveRight), SDL_SCANCODE_D, ButtonType::Pressed);
		InputManager::GetInstance().AddCommandKeyboard(std::move(moveLeft), SDL_SCANCODE_A, ButtonType::Pressed);
	}*/
	
	InputManager::GetInstance().AddCommandController(std::move(moveUp), Button::DPadUp, ButtonType::Pressed, m_PlayerIndex);
	InputManager::GetInstance().AddCommandController(std::move(moveDown), Button::DPadDown, ButtonType::Pressed, m_PlayerIndex);
	InputManager::GetInstance().AddCommandController(std::move(moveRight), Button::DPadRight, ButtonType::Pressed, m_PlayerIndex);
	InputManager::GetInstance().AddCommandController(std::move(moveLeft), Button::DPadLeft, ButtonType::Pressed, m_PlayerIndex);
	InputManager::GetInstance().AddCommandController(std::move(takeDamage), Button::ButtonA, ButtonType::onRelease, m_PlayerIndex);
	InputManager::GetInstance().AddCommandController(std::move(score), Button::ButtonB, ButtonType::onRelease, m_PlayerIndex);
}

void PlayerController::SetKeyboard()
{
	GameObject* owner{ GetOwner() };

	std::unique_ptr<dae::Command> moveUp = std::make_unique<dae::MoveCommand>(owner, glm::vec2{0, -1}, m_Speed);
	std::unique_ptr<dae::Command> moveDown = std::make_unique<dae::MoveCommand>(owner, glm::vec2{0, 1}, m_Speed);
	std::unique_ptr<dae::Command> moveRight = std::make_unique<dae::MoveCommand>(owner, glm::vec2{1, 0}, m_Speed);
	std::unique_ptr<dae::Command> moveLeft = std::make_unique<dae::MoveCommand>(owner, glm::vec2{-1, 0}, m_Speed);
	std::unique_ptr<dae::Command> takeDamage = std::make_unique<dae::DamageCommand>(owner);
	std::unique_ptr<dae::Command> score = std::make_unique<dae::ScoreCommand>(owner);

	using ButtonType = InputManager::InputType;

	InputManager::GetInstance().AddCommandKeyboard(std::move(moveUp), SDL_SCANCODE_W, ButtonType::Pressed);
	InputManager::GetInstance().AddCommandKeyboard(std::move(moveDown), SDL_SCANCODE_S, ButtonType::Pressed);
	InputManager::GetInstance().AddCommandKeyboard(std::move(moveRight), SDL_SCANCODE_D, ButtonType::Pressed);
	InputManager::GetInstance().AddCommandKeyboard(std::move(moveLeft), SDL_SCANCODE_A, ButtonType::Pressed);
	InputManager::GetInstance().AddCommandKeyboard(std::move(takeDamage), SDL_SCANCODE_E, ButtonType::onPress);
	InputManager::GetInstance().AddCommandKeyboard(std::move(score), SDL_SCANCODE_SPACE, ButtonType::onRelease);

	InputManager::GetInstance().SetActivityController(false, m_PlayerIndex);
}