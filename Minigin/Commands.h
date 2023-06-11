#pragma once
#include <glm/glm.hpp>


namespace dae
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* GameObject)
			:m_GameObject{GameObject}
		{}

		virtual ~GameActorCommand() = default;
	protected:
		GameObject* GetGameObject() const
		{
			return m_GameObject;
		}
	private:
		GameObject* m_GameObject;
	};

	class MoveCommand final : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* GameObject, const glm::vec2& direction, float speed)
			:GameActorCommand(GameObject),
			m_Direction{direction},
			m_Speed{speed}
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

	class ScoreCommand final : public GameActorCommand
	{
	public:
		ScoreCommand(GameObject* GameObject)
			:GameActorCommand(GameObject)
		{}

		void Execute() override;
	};
}

