#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class GameObject;
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner);
		virtual ~TransformComponent() = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent & other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override {};

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
		
		bool m_NeedsUpdate;
	};
}
