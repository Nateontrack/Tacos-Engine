#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "Transform.h"

namespace dae
{
	dae::GameObject::~GameObject()
	{
		for (auto& component : m_Components)
		{
			component.reset();
		}
		m_Components.clear();
	}

	void dae::GameObject::Update()
	{
		for (auto& component : m_Components) 
		{
			component->Update();
		}
	}

	void dae::GameObject::Render() const
	{
		for (auto& component : m_Components)
		{
			component->Render();
		}
	}
}

