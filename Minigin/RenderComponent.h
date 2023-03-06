#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Component.h"



namespace dae
{
	class Texture2D;
	class RenderComponent final : public Component
	{
	public:
		RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update() override {};
		virtual void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		void SetTransform(const glm::vec3& transform);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		glm::vec3 m_Transform{};
	};
}


