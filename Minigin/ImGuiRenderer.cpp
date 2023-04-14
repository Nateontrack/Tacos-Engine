#include <vector>
#include <imgui_plot.h>
#include <algorithm>
#include <chrono>
#include <numeric>
#include "ImGuiRenderer.h"


namespace dae
{
	//should become a component
	void ImGuiRenderer::Render()
	{
		//RenderExercise1();
		//RenderExercise2();
	}

	void ImGuiRenderer::RenderExercise1()
	{
		ImGui::Begin("Exercise1");

		static int samples = 50;
		ImGui::InputInt("samples", &samples);

		static bool drawGraph = false;
		static std::vector<float> measurements;
		if (ImGui::Button("Trash the cache"))
		{
			drawGraph = true;
			measurements.clear();
			TrashTheCache(measurements, samples);
		}
		if (drawGraph)
		{
			DrawGraph(measurements, ImColor{ 0, 255, 255 });
		}
		
		ImGui::End();
	}

	void ImGuiRenderer::RenderExercise2()
	{
		ImGui::Begin("Exercise2");
		ImColor yellow{ 255, 170, 0 }, blue{ 0, 0, 255 };
		static int samples = 50;
		ImGui::InputInt("samples", &samples);

		static bool drawGraphObject = false;
		static bool drawGraphObjectAlt = false;
		static std::vector<float> measurements;
		static std::vector<float> measurementsAlt;
		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			drawGraphObject = true; 
			measurements.clear();
			GameObject3D(measurements, samples);
		}
		if (drawGraphObject)
		{
			DrawGraph(measurements, blue);
		}

		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		{
			drawGraphObjectAlt = true;
			measurementsAlt.clear();
			GameObject3DAlt(measurementsAlt, samples);
			if (!drawGraphObject)
			{
				GameObject3D(measurements, samples);
			}
		}
		if (drawGraphObjectAlt)
		{
			DrawGraph(measurementsAlt, yellow);
			ImGui::Text("Combined:");
			DrawDoubleGraph(measurements, measurementsAlt, blue, yellow);
		}
		ImGui::End();
	}

	void ImGuiRenderer::DrawGraph(const std::vector<float>& measurements, ImColor color) const
	{
		ImGui::PlotConfig conf;
		conf.values.ys = measurements.data();
		conf.values.count = static_cast<int>(measurements.size());
		conf.values.color = color;
		conf.scale.min = 0;
		auto max_element = std::max_element(measurements.begin(), measurements.end());
		conf.scale.max = *max_element;
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;
		conf.frame_size = ImVec2(150, 75);
		conf.line_thickness = 2.f;
		

		ImGui::Plot("plot", conf);
	}

	void ImGuiRenderer::DrawDoubleGraph(const std::vector<float>& measurements1, const std::vector<float>& measurements2, ImColor color1, ImColor color2) const
	{
		static const float* y_data[] = { measurements1.data(), measurements2.data() };
		static ImU32 colors[] = { color1, color2 };
		static uint32_t selection_start = 0, selection_length = 0;

		ImGui::PlotConfig conf;
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.count = static_cast<int>(measurements1.size());
		conf.values.colors = colors;
		conf.scale.min = 0;
		auto max_element = std::max_element(measurements1.begin(), measurements1.end());
		conf.scale.max = *max_element;
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;
		conf.selection.show = true;
		conf.selection.start = &selection_start;
		conf.selection.length = &selection_length;
		conf.frame_size = ImVec2(150, 75);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}

	void ImGuiRenderer::TrashTheCache(std::vector<float>& measurements, int samples)
	{
		const int arrLength{ 1'000'000 };
		int* buffer{ new int[arrLength] };
		

		for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<float> benchmarks{};

			for (int it = 0; it < samples; it++)
			{
				auto t1{ std::chrono::high_resolution_clock::now() };


				for (size_t idx = 0; idx < arrLength; idx += stepSize)
				{
					buffer[idx] *= 2;
				}

				auto t2{ std::chrono::high_resolution_clock::now() };

				benchmarks.push_back(std::chrono::duration<float>{ t2 - t1 }.count());
			}

			for (int i = 0; i < samples / 10; ++i) // for every 10 measurements discard biggest & smallest
			{
				benchmarks.erase(std::max_element(benchmarks.begin(), benchmarks.end()));
				benchmarks.erase(std::min_element(benchmarks.begin(), benchmarks.end()));
			}
			
			float benchmark = std::accumulate(benchmarks.cbegin(), benchmarks.cend(), 0.f) / static_cast<float>(benchmarks.size());
			measurements.push_back(benchmark);
		}

		delete[] buffer;
		buffer = nullptr;
	}

	void ImGuiRenderer::GameObject3D(std::vector<float>& measurements, int samples)
	{
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};

		const int arrLength{ 1'000'000 };
		std::vector<GameObject3D> buffer{ arrLength };


		for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<float> benchmarks{};

			for (int it = 0; it < samples; it++)
			{
				auto t1{ std::chrono::high_resolution_clock::now() };


				for (size_t idx = 0; idx < arrLength; idx += stepSize)
				{
					buffer[idx].ID *= 2;
				}

				auto t2{ std::chrono::high_resolution_clock::now() };

				benchmarks.push_back(std::chrono::duration<float>{ t2 - t1 }.count());
			}

			for (int i = 0; i < samples / 10; ++i) // for every 10 measurements discard biggest & smallest
			{
				benchmarks.erase(std::max_element(benchmarks.begin(), benchmarks.end()));
				benchmarks.erase(std::min_element(benchmarks.begin(), benchmarks.end()));
			}

			float benchmark = std::accumulate(benchmarks.cbegin(), benchmarks.cend(), 0.f) / static_cast<float>(benchmarks.size());
			measurements.push_back(benchmark);
		}
	}

	void ImGuiRenderer::GameObject3DAlt(std::vector<float>& measurements, int samples)
	{
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};

		const int arrLength{ 1'000'000 };
		std::vector<GameObject3DAlt> buffer{ arrLength };


		for (size_t stepSize = 1; stepSize <= 1024; stepSize *= 2)
		{
			std::vector<float> benchmarks{};

			for (int it = 0; it < samples; it++)
			{
				auto t1{ std::chrono::high_resolution_clock::now() };


				for (size_t idx = 0; idx < arrLength; idx += stepSize)
				{
					buffer[idx].ID *= 2;
				}

				auto t2{ std::chrono::high_resolution_clock::now() };

				benchmarks.push_back(std::chrono::duration<float>{ t2 - t1 }.count());
			}

			for (int i = 0; i < samples / 10; ++i) // for every 10 measurements discard biggest & smallest
			{
				benchmarks.erase(std::max_element(benchmarks.begin(), benchmarks.end()));
				benchmarks.erase(std::min_element(benchmarks.begin(), benchmarks.end()));
			}

			float benchmark = std::accumulate(benchmarks.cbegin(), benchmarks.cend(), 0.f) / static_cast<float>(benchmarks.size());
			measurements.push_back(benchmark);
		}
	}
}

