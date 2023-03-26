#pragma once
#include <chrono>
#include <vector>

#include "ComponentBase.h"
#include "imgui_plot.h"

class TrashTheCacheComponent final : public dae::ComponentBase
{
public:
	TrashTheCacheComponent(dae::GameObject* parent);

	~TrashTheCacheComponent() = default;
	TrashTheCacheComponent(const TrashTheCacheComponent& other) = delete;
	TrashTheCacheComponent(TrashTheCacheComponent&& other) = delete;
	TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
	TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other) = delete;
	void RenderUI() override;
private:
	bool m_ShowDemo{ true };
	bool m_ShowEx1{ false };
	bool m_ShowEx2{ false };

	int intSamples{10};
	int gameObjSamples{10};

	ImGui::PlotConfig conf;
	ImGui::PlotConfig config;
	ImGui::PlotConfig config1;


	long long avg{};
	std::vector<float> plotDataInts{};
	std::vector<float> plotDataGO{};
	std::vector<float> plotDataGOA{};


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
		int ID{};
	};

	GameObject3D* g_GameObjectArr = new GameObject3D[gArrSize];


	class GameObject3DAlt
	{
	public:
		Transform* transform;
		int ID{};
	};

	GameObject3DAlt* g_GameObjectAltArr = new GameObject3DAlt[gArrSize];

	long long IterateInts(int stepSize, int samples = 12) const;

	long long IterateGameObjs(int stepSize, int samples = 12) const;

	long long IterateGameObjsAlt(int stepSize, int samples = 12) const;

	void Ex1(int stepsize, int, long long& average) const;
};
