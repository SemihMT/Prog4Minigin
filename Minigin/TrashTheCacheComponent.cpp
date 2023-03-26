#include "TrashTheCacheComponent.h"

TrashTheCacheComponent::TrashTheCacheComponent(dae::GameObject* parent):
ComponentBase(parent)
{
}

void TrashTheCacheComponent::RenderUI()
{
	constexpr float x_data[12]{ 1,2,4,8,16,32,64,128,256,512,1024,2048 };


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
	

}

long long TrashTheCacheComponent::IterateInts(int stepSize, int samples) const
{
	long long average{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_Array[j] *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		average += elapsedTime;
	}

	average /= samples;
	return average;

}

long long TrashTheCacheComponent::IterateGameObjs(int stepSize, int samples) const
{
	long long average{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_GameObjectArr[j].ID *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		average += elapsedTime;
	}

	average /= samples;
	return average;

}

long long TrashTheCacheComponent::IterateGameObjsAlt(int stepSize, int samples) const
{
	long long average{};
	for (int i{ 0 }; i < samples; ++i)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int j{ 0 }; j < gArrSize; j += stepSize)
			g_GameObjectAltArr[j].ID *= 2;
		auto end = std::chrono::high_resolution_clock::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		average += elapsedTime;
	}

	average /= samples;
	return average;

}

void TrashTheCacheComponent::Ex1(int stepsize, int, long long& average) const
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
