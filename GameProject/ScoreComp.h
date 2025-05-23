#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <memory>
#include <Component.h>
#include <Subject.h>
#include <Sound.h>


//-----------------------------------------------------
// Class Forwards									
//-----------------------------------------------------


class ScoreComp final : public dae::Component	//Args: 
{
public:
	ScoreComp(dae::GameObject& parent);	

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	ScoreComp(const ScoreComp& other)						= default;
	ScoreComp(ScoreComp&& other) noexcept					= default;
	ScoreComp& operator=(const ScoreComp& other)			= default;
	ScoreComp& operator=(ScoreComp&& other) noexcept		= default;

	// -------------------------
	// Base Functions
	// -------------------------  
	//void Start() override;
	//void FixedUpdate(float deltaFixedTime) override;
	//void Update(float deltaTime) override;
	//void LateUpdate(float deltaTime) override;
	//void Render() const override;
	//--------------------------

	void AddScore(int amount);

	int GetScore() const;

	dae::Subject& OnScoreChanged();

private: 

	int m_Score{ 0 };

	std::unique_ptr<dae::Subject> m_ScoreChangedEvent;
	dae::SoundToken m_ScoreChangedSoundToken{m_ScoreChangedSoundEntry};

	static constexpr dae::SoundEntry m_ScoreChangedSoundEntry{ "TestSounds/Bomberman SFX (6).wav" };
};

 
