#pragma once
#include <string>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Component;
	class TextComponent;
	class GameObject;

	class HealthDisplay : public Component, public Observer<int>
	{
	public:
		HealthDisplay(GameObject* pOwner);
		virtual void Update() override;
		virtual void Render() const override {}

		virtual void OnNotify(int health) override;
		virtual void OnSubjectDestroy() override;

		void SetDisplayString(const std::string& str);

		HealthDisplay(const HealthDisplay& other) = delete;
		HealthDisplay(HealthDisplay&& other) = delete;
		HealthDisplay& operator=(const HealthDisplay& other) = delete;
		HealthDisplay& operator=(HealthDisplay&& other) = delete;
		virtual ~HealthDisplay() = default;
	private:

		std::unique_ptr<TextComponent> m_TextComp;
		std::string m_DisplayString;
	};
}