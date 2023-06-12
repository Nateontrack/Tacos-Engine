#pragma once
#include "Observer.h"


namespace dae
{
	class Component;
	class GameObject;


	class ScoreComponent final : public Component, public Observer<>
	{
	public:
		ScoreComponent(GameObject* pOwner, int playerIndex);

		virtual ~ScoreComponent() = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override {}

		void Reset();
		virtual void OnNotify() override {}
		virtual void OnSubjectDestroy() override;
		
		void SetObserver(Observer<int>* hud);
		
		int GetScore() const;

	private:
		void GainScore();

		int m_Increment;
		int m_CurrentScore;
		int m_PlayerIndex;

		Subject<int> m_ScorePoints;
	};
}

