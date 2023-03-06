#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	RenderComponent::RenderComponent(GameObject* pOwner)
		:Component(pOwner)
	{}

	void RenderComponent::Render() const
	{
		if (m_pTexture != nullptr)
		{
			const auto& pos = m_Transform;
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}

	void RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
	{
		m_pTexture = pTexture;
	}

	void RenderComponent::SetTransform(const glm::vec3& transform)
	{
		m_Transform = transform;
	}
}