#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "ImGuiRenderer.h"
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class ImGuiRenderer;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		std::unique_ptr<ImGuiRenderer> m_ImGuiRenderer;
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const glm::vec2& dst, const glm::vec2& src, const float srcWidth, const float srcHeight, const float sizeFactor = 1.f) const;
		
		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

