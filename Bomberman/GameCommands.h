#pragma once
#include "Commands.h"

namespace dae
{
	class MoveCommand final : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* GameObject, const glm::vec2& direction, float speed)
			:GameActorCommand(GameObject),
			m_Direction{ direction },
			m_Speed{ speed }
		{}

		virtual ~MoveCommand() = default;

		void Execute() override;

	private:
		float m_Speed;
		glm::vec2 m_Direction;
	};

	class DamageCommand final : public GameActorCommand
	{
	public:
		DamageCommand(GameObject* GameObject)
			:GameActorCommand(GameObject)
		{}

		void Execute() override;
	};

	class BombCommand final : public GameActorCommand
	{
	public:
		BombCommand(GameObject* GameObject)
			:GameActorCommand(GameObject)
		{}

		void Execute() override;
	};
}



