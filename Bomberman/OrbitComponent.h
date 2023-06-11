#pragma once
#include <glm/glm.hpp>
#include "Component.h"


namespace dae
{
	class OrbitComponent final : public Component
	{
	public:
		OrbitComponent(GameObject* pOwner);
		virtual ~OrbitComponent() = default;

		OrbitComponent(const OrbitComponent& other) = delete;
		OrbitComponent(OrbitComponent&& other) = delete;
		OrbitComponent& operator=(const OrbitComponent& other) = delete;
		OrbitComponent& operator=(OrbitComponent&& other) = delete;

		virtual void Update();
		virtual void Render() const {};

		void SetRadius(float radius) { m_Radius = radius; }
		void SetSpeed(float speed) { m_RotationSpeed = speed; }
		void SetRotateDirection(bool isClockwise) { m_RotatesClockwise = isClockwise; }
		void SetIsRotating(bool isRotating) { m_IsRotating = isRotating; }

	private:
		float m_Radius;
		float m_RotationSpeed;
		float m_Angle;
		bool m_RotatesClockwise;
		bool m_IsRotating;
	};

}

