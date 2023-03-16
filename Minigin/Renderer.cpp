#include "Renderer.h"

#include <chrono>
#include <numeric>
#include <stdexcept>

#include "imgui.h"
#include "implot.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}


void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();


	RenderImGui();


	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

void dae::Renderer::AddImGuiFrame()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

void dae::Renderer::EndImGuiFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


//WEEK 4 : TRASH THE CACHE EXERCISE


const int gArrSize{ 10'000'000 };
int* g_Array = new int[gArrSize];


struct Transform
{
	float matrix[16] =
	{
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

GameObject3D* g_GameObjectArr = new GameObject3D[gArrSize];


class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

GameObject3DAlt* g_GameObjectAltArr = new GameObject3DAlt[gArrSize];

long long IterateInts(int stepSize, int samples = 12)
{
	long long avg{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_Array[j] *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		avg += elapsedTime;
	}

	avg /= samples;
	return avg;

}

long long IterateGameObjs(int stepSize, int samples = 12)
{
	long long avg{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_GameObjectArr[j].ID *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		avg += elapsedTime;
	}

	avg /= samples;
	return avg;

}

long long IterateGameObjsAlt(int stepSize, int samples = 12)
{
	long long avg{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_GameObjectAltArr[j].ID *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		avg += elapsedTime;
	}

	avg /= samples;
	return avg;

}

void Ex1(int stepsize, int, long long& average)
{
	const int arrSize{ 10'000 };
	int* array = new int[arrSize];

	for (int repeat{ 0 }; repeat < 100; ++repeat)
	{

		auto start = std::chrono::high_resolution_clock::now();
		for (int i{ 0 }; i < arrSize; i += stepsize)
			array[i] *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		average += elapsedTime;

		//std::cout << "operation took " << elapsedTime << " ns" << std::endl;


	}
	average /= 100;
	delete[] array;
}

void dae::Renderer::RenderImGui()
{
	constexpr float x_data[12]{ 1,2,4,8,16,32,64,128,256,512,1024,2048 };

	AddImGuiFrame();

	//Placing brackets after each "Begin" to organize stuff
	ImGui::Begin("Ex1", &m_ShowDemo, 0);

	ImGui::Text("Application avg %.3f ms/frame (%.1f FPS)", 1000.0f / float(ImGui::GetIO().Framerate), float(ImGui::GetIO().Framerate));

	conf.values.xs = x_data; // this line is optional
	
	conf.values.color = ImColor(0,0,255);
	plotDataInts.resize(11);

	
	ImGui::SliderInt("Samples",&intSamples,10,25);

	if (ImGui::Button("Exercise 1") && m_ShowEx1 == false)
	{
		m_ShowEx1 = true;
		int counter{ 0 };
		for (int i{ 1 }; i <= 1024; i *= 2)
		{
			plotDataInts[counter] = static_cast<float>(IterateInts(i,intSamples));
			++counter;
		}
		delete[] g_Array;
		conf.values.ys = plotDataInts.data();
		conf.values.count = static_cast<int>(plotDataInts.size()) + 1;
		conf.scale.min = 0;
		conf.scale.max = plotDataInts[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 200);
		conf.line_thickness = 2.f;
		
	}
	if(m_ShowEx1)
	{
		ImGui::Plot("plot", conf);
	}
	ImGui::End();
	

	
	
	ImGui::Begin("Ex2", &m_ShowDemo);
	
	config.values.xs = x_data;
	config1.values.xs = x_data;

	config.values.color = ImColor(128,0,56);
	config1.values.color = ImColor(200,0,112);
	
	ImGui::SliderInt("Samples",&gameObjSamples,10,25);
	plotDataGO.resize(11);
	plotDataGOA.resize(11);
	
	if (ImGui::Button("Exercise 2") && m_ShowEx2 == false)
	{
		m_ShowEx2 = true;
		int counter{ 0 };
		for (int i{ 1 }; i <= 1024; i *= 2)
		{
			plotDataGO[counter] = static_cast<float>(IterateGameObjs(i,gameObjSamples));
			plotDataGOA[counter] = static_cast<float>(IterateGameObjsAlt(i,gameObjSamples));
			++counter;
		}
		delete[] g_GameObjectArr;
		delete[] g_GameObjectAltArr;
		config.values.ys = plotDataGO.data();
		config.values.count = static_cast<int>(plotDataGO.size()) + 1;
		config.scale.min = 0;
		config.scale.max = plotDataGO[0];
		config.tooltip.show = true;
		config.tooltip.format = "x=%.2f, y=%.2f";
		config.grid_x.show = true;
		config.grid_y.show = true;
		config.frame_size = ImVec2(200, 200);
		config.line_thickness = 2.f;

		config1.values.ys = plotDataGOA.data();
		config1.values.count = static_cast<int>(plotDataGOA.size()) + 1;
		config1.scale.min = 0;
		config1.scale.max = plotDataGOA[0];
		config1.tooltip.show = true;
		config1.tooltip.format = "x=%.2f, y=%.2f";
		config1.grid_x.show = true;
		config1.grid_y.show = true;
		config1.frame_size = ImVec2(200, 200);
		config1.line_thickness = 2.f;

	}
	if(m_ShowEx2)
	{
		ImGui::Plot("plot", config);
		ImGui::Plot("plot2",config1);
		
		
	}

	ImGui::End();
	

	EndImGuiFrame();
}

