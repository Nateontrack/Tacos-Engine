#pragma once
struct ImColor;
namespace dae
{
	class ImGuiRenderer final
	{
	public:
		ImGuiRenderer() = default;
		~ImGuiRenderer() = default;

		ImGuiRenderer(const ImGuiRenderer& other) = delete;
		ImGuiRenderer(ImGuiRenderer&& other) = delete;
		ImGuiRenderer& operator=(const ImGuiRenderer& other) = delete;
		ImGuiRenderer& operator=(ImGuiRenderer&& other) = delete;

		void Render();
	private:
		void RenderExercise1();
		void RenderExercise2();
		void DrawGraph(const std::vector<float>& measurements, ImColor color) const;
		void DrawDoubleGraph(const std::vector<float>& measurements1, const std::vector<float>& measurements2, ImColor color1, ImColor color2) const;
		void TrashTheCache(std::vector<float>& measurements, int samples);
		void GameObject3D(std::vector<float>& measurements, int samples);
		void GameObject3DAlt(std::vector<float>& measurements, int samples);
	};
}


