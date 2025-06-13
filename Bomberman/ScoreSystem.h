#ifndef SCORESYSTEM
#define SCORESYSTEM

#include "IScoreSystem.h"

namespace bm
{
	class Null_ScoreSystem final : public IScoreSystem
	{
	public:

		// Inherited via IScoreSystem
		int GetScore() const override { return 0; };
		void AddScore(int) override {};
		void ResetScore() override {};
		void SetScore(int) override {};
		bool IsHighScore() const override { return false; };
		void AddHighScore(std::string) override {};
		const std::vector<HighScore>& GetHighScores() const override { throw std::runtime_error("Cannot use GetHighScore with Null_Scoresystem, register another before using"); };
	};

	class Default_ScoreSystem final : public IScoreSystem
	{
	public:
		Default_ScoreSystem();

		int GetScore() const override;

		void AddScore(int amount) override;
		void ResetScore() override;
		void SetScore(int score) override;

		bool IsHighScore() const override;
		void AddHighScore(std::string name) override;

		const std::vector<HighScore>& GetHighScores() const override;

	private:

		void LoadHighScores();
		void SaveHighScores();

		static constexpr std::string_view s_HighScoreFilePath{ "highscores.txt" };
		static constexpr int s_MaxAmountOfHighScores{ 5 };

		int m_CurrentScore{ 0 };
		std::vector<HighScore> m_HighScores{};
	};
}

#endif // !SCORESYSTEM
