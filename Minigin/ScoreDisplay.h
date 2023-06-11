#pragma once
#include <string>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Component;
	class TextComponent;
	class GameObject;

	class ScoreDisplay : public Component, public Observer<int>
	{
	public:
		ScoreDisplay(GameObject* pOwner);
		virtual void Update() override;
		virtual void Render() const override {}

		virtual void OnNotify(int health) override;
		virtual void OnSubjectDestroy() override;

		void SetDisplayString(const std::string& str);


		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;
		virtual ~ScoreDisplay() = default;
	private:

		std::unique_ptr<TextComponent> m_TextComp;
		std::string m_DisplayString;
	};
}
