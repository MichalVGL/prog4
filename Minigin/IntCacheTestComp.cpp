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

#include "IntCacheTestComp.h"
#include "imgui.h"

IntCacheTestComp::IntCacheTestComp(dae::GameObject& parent)
	:Component(parent)
	, m_Measuring{false}
	, m_Results{ std::make_shared<std::vector<float>>() }
	, m_plotConfig{}
	, m_Samples{ 10 }
{
	m_plotConfig.values.ys_count = 1;
	m_plotConfig.grid_y.show = true;
	m_plotConfig.frame_size.x = 220.f;
	m_plotConfig.frame_size.y = 140.f;
	m_plotConfig.values.color = IM_COL32(255, 100, 0, 255);
}


void IntCacheTestComp::MeasureInt(int samples)
{
	//delete old results(if any)
	m_Results.store(std::make_shared<std::vector<float>>());

	//measuring code
	const int ARRSIZE{ 67108864 };

	m_Measuring = true;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

	std::vector<int> arr{};
	arr.reserve(ARRSIZE);

	for (int i = 0; i < ARRSIZE; ++i)
	{
		arr.emplace_back(i);
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
				arr[i] *= 2;
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

	m_Results.store(std::make_shared<decltype(averageTimes)>(std::move(averageTimes)));

	m_Measuring = false;
}

void IntCacheTestComp::UpdateImGui()
{
	ImGui::Begin("Exercise 1");

	//input/measuring
	ImGui::InputInt("Samples", &m_Samples);
	if (m_Samples < 3)
		m_Samples = 3;

	if (!m_Measuring)
	{
		if (ImGui::Button("Thrash the Cache with integers"))
		{
			std::thread(std::bind(&IntCacheTestComp::MeasureInt, this, m_Samples)).detach();
		}
	}
	else
	{
		ImGui::Text("Measuring...");
	}

	//visualize results
	auto results = m_Results.load();
	if (results->size() > 0)
	{
		m_plotConfig.values.ys = &(results->front());
		m_plotConfig.grid_y.size = results->front() / 10.f;	//10 lines
		m_plotConfig.values.count = static_cast<int>(results->size());
		m_plotConfig.scale.max = results->front();

		ImGui::Plot("int plot", m_plotConfig);
	}

	ImGui::End();
}






