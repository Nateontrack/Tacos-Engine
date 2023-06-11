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
}

