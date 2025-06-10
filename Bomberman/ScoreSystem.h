#ifndef SCORESYSTEM
#define SCORESYSTEM

#include "IScoreSystem.h"

namespace bm
{
	class ScoreSystem final : public IScoreSystem
	{
	public:
		ScoreSystem();

		int GetScore() const override;

		void AddScore(int amount) override;

		void ResetScore() override;
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
