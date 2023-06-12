#include "BombComponent.h"
#include "GameObject.h"
#include "Timer.h"


using namespace dae;

BombComponent::BombComponent(GameObject* pOwner)
	:Component(pOwner),
	m_State{ BombState::fuse },
	m_Exploded{},
	m_ChargeTimer{ 0.f },
	m_Charges {3}
{
	m_AnimationSheet = std::make_unique<AnimationSheetComponent>(pOwner);
	m_AnimationSheet->CreateAnimationsFromFile("../Data/LoadingData/BombAnimations.xml");
	m_AnimationSheet->SetAnimKey(static_cast<int>(m_State));
}

void BombComponent::Update()
{
	switch (m_State)
	{
	case dae::BombComponent::BombState::fuse:
		FuseState();
		break;
	case dae::BombComponent::BombState::explode:
		ExplodeState();
		break;
	}

	m_AnimationSheet->Update();
}

void BombComponent::SetObserver(Observer<>* scoreComponent)
{
	m_Exploded.AddObserver(scoreComponent);
}

void BombComponent::FuseState()
{
	m_ChargeTimer += Timer::GetInstance()->GetElapsedSec();

	if (m_ChargeTimer > m_Charges * m_AnimationSheet->GetAnimationTime(static_cast<int>(BombState::fuse)))
	{
		m_State = BombState::explode;
		m_AnimationSheet->SetAnimKey(static_cast<int>(m_State));
		m_ChargeTimer = 0.f;
	}
}

void BombComponent::ExplodeState()
{
	m_ChargeTimer += Timer::GetInstance()->GetElapsedSec();
	if (m_ChargeTimer > m_AnimationSheet->GetAnimationTime(static_cast<int>(BombState::explode)))
	{
		GetOwner()->MarkForDeletion();
	}
}

int BombComponent::GetState() const
{
	return static_cast<int>(m_State);
}