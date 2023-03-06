#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* pOwner);
		virtual void Update() override;
		virtual void Render() const override {};

		void SetText(const std::string& text);
		Texture2D* GetTexture() const;

		

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
		virtual ~TextComponent() = default;
	private:
		
		bool m_NeedsUpdate;
		std::string m_Text;
		glm::vec3 m_Color;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}



