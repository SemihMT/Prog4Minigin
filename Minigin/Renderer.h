#pragma once
#include <SDL.h>
#include <vector>

#include "imgui_plot.h"
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	private:
		bool m_ShowDemo{ true };
		bool m_ShowEx1{ false };
		bool m_ShowEx2{ false };

		int intSamples{};
		int gameObjSamples{};

		ImGui::PlotConfig conf;
		ImGui::PlotConfig config;
		ImGui::PlotConfig config1;


		long long avg{};
		std::vector<float> plotDataInts{};
		std::vector<float> plotDataGO{};
		std::vector<float> plotDataGOA{};
		void AddImGuiFrame();
		void EndImGuiFrame();
		void RenderImGui();
	};
}

