#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"

namespace dae
{
	RenderComponent::RenderComponent(GameObject* pOwner)
		:Component(pOwner)
	{}

	void RenderComponent::Render() const
	{
		if (m_pTexture != nullptr)
		{
			const auto& pos = GetOwner()->GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}

	void RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
	{
		m_pTexture = pTexture;
	}

	void RenderComponent::SetSource(const glm::vec2& srcPos, const float srcWidth, const float srcHeight, const float sizeFactor)
	{
		m_HasSource = true;
		m_SrcPos = srcPos;
		m_SrcWidth = srcWidth;
		m_SrcHeight = srcHeight;
		m_SizeFactor = sizeFactor;
	}
}