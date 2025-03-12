#ifndef INTCACHETESTCOMP_H
#define INTCACHETESTCOMP_H
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <atomic>
#include <memory>
#include "Component.h"
#include "imgui_plot.h"


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------


class IntCacheTestComp final : public Component	//Args: 
{
public:
	IntCacheTestComp(dae::GameObject& parent);	

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	IntCacheTestComp(const IntCacheTestComp& other)						= default;
	IntCacheTestComp(IntCacheTestComp&& other) noexcept					= default;
	IntCacheTestComp& operator=(const IntCacheTestComp& other)			= default;
	IntCacheTestComp& operator=(IntCacheTestComp&& other) noexcept		= default;

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

	std::atomic<bool> m_Measuring;
	std::atomic<std::shared_ptr<std::vector<float>>> m_Results;
	ImGui::PlotConfig m_plotConfig;
	int m_Samples;

	void MeasureInt(int samples);

};
 
#endif // INTCACHETESTCOMP_H