#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "GameObject.h"


namespace dae
{
	TextComponent::TextComponent(GameObject* pOwner)
		:Component(pOwner),
		m_Text{},
		m_Font{nullptr},
		m_Color{255, 255, 0},
		m_NeedsUpdate{true}
	{
		m_Font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	}

	void TextComponent::Update()
	{
		if (m_NeedsUpdate)
		{
			const SDL_Color color = { static_cast<Uint8>(m_Color.x),static_cast<Uint8>(m_Color.y),static_cast<Uint8>(m_Color.z) };
			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_TextTexture = std::make_shared<Texture2D>(texture);
			GetOwner()->GetComponent<RenderComponent>()->SetTexture(m_TextTexture);
			m_NeedsUpdate = false;
		}
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	Texture2D* TextComponent::GetTexture() const
	{
		return m_TextTexture.get();
	}
}

