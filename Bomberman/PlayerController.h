#pragma once
#include "Component.h"
#include "Observer.h"
#include "AnimationSheetComponent.h"

namespace dae
{
	class HealthComponent;
	class ScoreComponent;

	class PlayerController final : public Component
	{
	public:
		enum class PlayerState
		{
			moveLeft = 0,
			moveDown = 1,
			moveRight = 2,
			moveUp = 3,
			die = 4,
			idle = 5
		};

		PlayerController(GameObject* pOwner);

		virtual ~PlayerController() = default;

		virtual void Update() override;
		virtual void Render() const override {};

		PlayerController(const PlayerController& other) = delete;
		PlayerController(PlayerController&& other) = delete;
		PlayerController& operator=(const PlayerController& other) = delete;
		PlayerController& operator=(PlayerController&& other) = delete;

		void PlaceBomb();
		void SetObserver(Observer<int>* hud);
		void SetKeyboard();
		void SetState(PlayerState state);

		int GetState() const;

		void AddMovement(const glm::vec2& movement);

	private:
		void InitCommands();

		void MovementState();
		void DieState();

		void Die(); //action after animation

		static int s_InstanceCount; // Static member variable to keep track of instance count
		const int m_MaxInstanceCount;
		int m_PlayerIndex;
		PlayerState m_State;
		float m_DeathTimer;
		float m_BombTimer;
		const float m_BombCooldown;
		bool m_OnCooldownBomb;

		glm::vec2 m_CurrentMovement;

		const float m_Speed;

		std::unique_ptr<ScoreComponent> m_ScoreComp;
		std::unique_ptr<HealthComponent> m_HealthComp;
		std::unique_ptr<AnimationSheetComponent> m_AnimationSheet;
	};
}



