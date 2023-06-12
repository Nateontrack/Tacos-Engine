#pragma once
#include <map>
#include <string>
#include "component.h"
#include "Observer.h"
#include "AnimationComponent.h"

namespace dae
{
	class Texture2D;

	class AnimationSheetComponent final : public Component, public Observer<int>
	{
	public:
		AnimationSheetComponent(GameObject* pOwner);
		virtual void Update() override;
		virtual void Render() const override {};
		virtual void OnNotify(int animKey) override;
		virtual void OnSubjectDestroy() override {};

		Texture2D* GetTexture() const;

		void CreateAnimationsFromFile(const std::string& filePath);

		float GetAnimationTime(int animKey);
		void SetPaused(bool paused);

		AnimationSheetComponent(const AnimationSheetComponent& other) = delete;
		AnimationSheetComponent(AnimationSheetComponent&& other) = delete;
		AnimationSheetComponent& operator=(const AnimationSheetComponent& other) = delete;
		AnimationSheetComponent& operator=(AnimationSheetComponent&& other) = delete;
		virtual ~AnimationSheetComponent() = default;
	private:

		void LoadAnimationsFromString(const std::string& spriteSheetData);
		void CreateAnimation(const std::string& animationData);

		int m_CurrentAnimKey{};

		using AnimationMap = std::map<int, std::unique_ptr<AnimationComponent>>;

		AnimationMap m_Animations;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


