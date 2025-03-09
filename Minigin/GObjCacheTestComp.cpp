//---------------------------
// Include Files
//---------------------------
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <thread>

#include "GObjCacheTestComp.h"

const ImU32 GObjCacheTestComp::PLOTCOLORS[2] = {
	IM_COL32(0, 255, 0, 255), 
	IM_COL32(255, 0, 0, 255)};

GObjCacheTestComp::GObjCacheTestComp(dae::GameObject& parent)
	:Component(parent)
	, m_GObjMeasuring{false}
	, m_GObjAltMeasuring{false}
	, m_GObjResults{ std::make_shared<std::vector<float>>() }
	, m_GObjAltResults{ std::make_shared<std::vector<float>>() }
	, m_GObjPlotConfig{}
	, m_GObjAltPlotConfig{}
	, m_CombiPlotConfig{}
	, m_Samples{ 10 }
{
	m_GObjPlotConfig.values.ys_count = 1;
	m_GObjPlotConfig.grid_y.show = true;
	m_GObjPlotConfig.frame_size.x = 220.f;
	m_GObjPlotConfig.frame_size.y = 140.f;
	m_GObjPlotConfig.values.color = PLOTCOLORS[0];

	m_GObjAltPlotConfig.values.ys_count = 1;
	m_GObjAltPlotConfig.grid_y.show = true;
	m_GObjAltPlotConfig.frame_size.x = 220.f;
	m_GObjAltPlotConfig.frame_size.y = 140.f;
	m_GObjAltPlotConfig.values.color = PLOTCOLORS[1];

	m_CombiPlotConfig.values.ys_count = 2;
	m_CombiPlotConfig.grid_y.show = true;
	m_CombiPlotConfig.frame_size.x = 220.f;
	m_CombiPlotConfig.frame_size.y = 140.f;
	m_CombiPlotConfig.values.colors = PLOTCOLORS;
}

void GObjCacheTestComp::UpdateImGui()
{
	ImGui::Begin("Exercise 2");

	ImGui::InputInt("Samples", &m_Samples);
	if (m_Samples < 3)
		m_Samples = 3;

	//GObj============================================================================
	//measuring
	if (!m_GObjMeasuring)
	{
		if (ImGui::Button("Thrash the Cache with GameObject"))
		{
			std::thread(std::bind(&GObjCacheTestComp::MeasureGobj, this, m_Samples)).detach();
		}
	}
	else
	{
		ImGui::Text("Measuring...");
	}

	//visualize results
	auto gObjResults = m_GObjResults.load();
	if (gObjResults->size() > 0)
	{
		m_GObjPlotConfig.values.ys = &(gObjResults->front());
		m_GObjPlotConfig.grid_y.size = gObjResults->front() / 10.f;	//10 lines
		m_GObjPlotConfig.values.count = static_cast<int>(gObjResults->size());
		m_GObjPlotConfig.scale.max = gObjResults->front();

		ImGui::Plot("GObj plot", m_GObjPlotConfig);
	}

	//GObjAlt============================================================================
	//measuring
	if (!m_GObjAltMeasuring)
	{
		if (ImGui::Button("Thrash the Cache with GameObjectAlt"))
		{
			std::thread(std::bind(&GObjCacheTestComp::MeasureGobjAlt, this, m_Samples)).detach();
		}
	}
	else
	{
		ImGui::Text("Measuring...");
	}

	//visualize results
	auto gObjAltResults = m_GObjAltResults.load();
	if (gObjAltResults->size() > 0)
	{
		m_GObjAltPlotConfig.values.ys = &(gObjAltResults->front());
		m_GObjAltPlotConfig.grid_y.size = gObjAltResults->front() / 10.f;	//10 lines
		m_GObjAltPlotConfig.values.count = static_cast<int>(gObjAltResults->size());
		m_GObjAltPlotConfig.scale.max = gObjAltResults->front();

		ImGui::Plot("GObjAlt plot", m_GObjAltPlotConfig);
	}

	//Combination============================================================================
	if (gObjResults->size() > 0 and gObjAltResults->size() > 0)
	{
		ImGui::Text("Combined: ");

		const float* compResults[2] = { gObjResults.get()->data(), gObjAltResults.get()->data()};
		m_CombiPlotConfig.values.ys_list = compResults;
		m_CombiPlotConfig.grid_y.size = gObjResults->front() / 10.f;	//10 lines
		m_CombiPlotConfig.values.count = static_cast<int>(gObjResults->size());
		m_CombiPlotConfig.scale.max = gObjResults->front();

		ImGui::Plot("Combination plot", m_CombiPlotConfig);
	}

	ImGui::End();
}

static const int ARRSIZE{ 2000000 };

void GObjCacheTestComp::MeasureGobj(int samples)
{
	//delete old results(if any)
	m_GObjResults.store(std::make_shared<std::vector<float>>());

	//measuring code
	m_GObjMeasuring = true;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

	std::vector<TestGameObject> arr{};
	arr.reserve(ARRSIZE);

	for (int i = 0; i < ARRSIZE; ++i)
	{
		arr.emplace_back();
	}

	std::vector<float> averageTimes{};
	std::vector<long long> sampleTimes{};

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		for (int sample = 0; sample < samples; ++sample)
		{

			start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < arr.size(); i += stepSize)
			{
				arr[i].ID += stepSize;
			}

			end = std::chrono::high_resolution_clock::now();

			sampleTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
		}
		//delete min and max element
		auto min = std::min_element(sampleTimes.begin(), sampleTimes.end());
		sampleTimes.erase(min);

		auto max = std::max_element(sampleTimes.begin(), sampleTimes.end());
		sampleTimes.erase(max);

		//add average time to end result
		averageTimes.push_back(static_cast<float>(std::accumulate(sampleTimes.begin(), sampleTimes.end(), 0LL) / sampleTimes.size()));
		sampleTimes.clear();
	}

	m_GObjResults.store(std::make_shared<std::vector<float>>(std::move(averageTimes)));

	m_GObjMeasuring = false;
}

void GObjCacheTestComp::MeasureGobjAlt(int samples)
{
	//delete old results(if any)
	m_GObjAltResults.store(std::make_shared<std::vector<float>>());

	//measuring code
	m_GObjAltMeasuring = true;

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

	std::vector<TestGameObjectAlt> arr{};
	arr.reserve(ARRSIZE);

	for (int i = 0; i < ARRSIZE; ++i)
	{
		arr.emplace_back();
	}

	std::vector<float> averageTimes{};
	std::vector<long long> sampleTimes{};

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		for (int sample = 0; sample < samples; ++sample)
		{

			start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < arr.size(); i += stepSize)
			{
				arr[i].ID += stepSize;
			}

			end = std::chrono::high_resolution_clock::now();

			sampleTimes.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
		}

		//delete min and max element
		auto min = std::min_element(sampleTimes.begin(), sampleTimes.end());
		sampleTimes.erase(min);

		auto max = std::max_element(sampleTimes.begin(), sampleTimes.end());
		sampleTimes.erase(max);

		//add average time to end result
		averageTimes.push_back(static_cast<float>(std::accumulate(sampleTimes.begin(), sampleTimes.end(), 0LL) / sampleTimes.size()));
		sampleTimes.clear();
	}

	m_GObjAltResults.store(std::make_shared<std::vector<float>>(std::move(averageTimes)));

	m_GObjAltMeasuring = false;
}




