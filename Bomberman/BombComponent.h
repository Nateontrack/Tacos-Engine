#pragma once
#include "Component.h"
#include "Observer.h"
#include "AnimationSheetComponent.h"


namespace dae
{
	class GameObject;

	class BombComponent : public Component
	{
	public:
		enum class BombState
		{
			fuse,
			explode
		};

		BombComponent(GameObject* pOwner);

		virtual ~BombComponent() = default;

		virtual void Update() override;
		virtual void Render() const override {};

		void SetObserver(Observer<>* scoreComponent);
		int GetState() const;

		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;
	private:
		
		void FuseState();
		void ExplodeState();
		

		Subject<> m_Exploded;
		std::unique_ptr<AnimationSheetComponent> m_AnimationSheet;

		BombState m_State;
		float m_ChargeTimer;
		const int m_Charges;
	};
}



