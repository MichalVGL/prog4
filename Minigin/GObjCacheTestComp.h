#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <atomic>
#include <memory>
#include "Component.h"
#include "ImGui.h"
#include "imgui_plot.h"


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------


class GObjCacheTestComp final : public Component	//Args: 
{
public:
	GObjCacheTestComp(dae::GameObject& parent);	

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	GObjCacheTestComp(const GObjCacheTestComp& other)						= default;
	GObjCacheTestComp(GObjCacheTestComp&& other) noexcept					= default;
	GObjCacheTestComp& operator=(const GObjCacheTestComp& other)			= default;
	GObjCacheTestComp& operator=(GObjCacheTestComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	void UpdateImGui() override;
	//--------------------------



private: 

	std::atomic<bool> m_GObjMeasuring;
	std::atomic<bool> m_GObjAltMeasuring;
	std::atomic<std::shared_ptr<std::vector<float>>> m_GObjResults;
	std::atomic<std::shared_ptr<std::vector<float>>> m_GObjAltResults;
	ImGui::PlotConfig m_GObjPlotConfig;
	ImGui::PlotConfig m_GObjAltPlotConfig;
	ImGui::PlotConfig m_CombiPlotConfig;
	int m_Samples;

	static const ImU32 PLOTCOLORS[2];

	void MeasureGobj(int samples);
	void MeasureGobjAlt(int samples);

};

//Test Object Definitions

struct TestTransform
{
	static const int MATRIXSIZE{ 16 };
	float matrix[MATRIXSIZE] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class TestGameObject
{
public:
	TestGameObject()
		:transform{}
		, ID{}
	{
	}

	TestTransform transform;
	int ID;
};

class TestGameObjectAlt
{
public:
	TestGameObjectAlt()
		:transform{ std::make_unique<TestTransform>() }
		, ID{}
	{
	}

	std::unique_ptr<TestTransform> transform;
	int ID;
};

 
