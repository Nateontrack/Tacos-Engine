#pragma once
#include "GameObject.h"
namespace dae
{
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
	protected:
		GameObject* GetGameObject() const
		{
			return m_GameObject;
		}
	private:
		GameObject* m_GameObject;
	};

	class Move final : public GameActorCommand
	{
	public:
		void Execute() override
		{ GetGameObject(); }
	private:
		float m_Speed;
		//float m_Acceleration;
		
	};
}

