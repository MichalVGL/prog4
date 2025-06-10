#include "ScoreSystem.h"

#include <filesystem>
#include <fstream>
#include <algorithm>

bm::ScoreSystem::ScoreSystem()
{
	LoadHighScores();
}

int bm::ScoreSystem::GetScore() const
{
	return m_CurrentScore;
}

void bm::ScoreSystem::AddScore(int amount)
{
	m_CurrentScore += amount;
}

void bm::ScoreSystem::ResetScore()
{
	m_CurrentScore = 0;
}

bool bm::ScoreSystem::IsHighScore() const
{
	if (m_HighScores.empty())
		return true; // no high scores, so any score is a high score
	return m_CurrentScore > m_HighScores.back().score;
}

void bm::ScoreSystem::AddHighScore(std::string name)
{
	if (name.empty())
		return;

	m_HighScores.push_back(HighScore{ .name = std::move(name), .score = m_CurrentScore });
	//resort the high scores
	std::sort(m_HighScores.begin(), m_HighScores.end(),
		[](const HighScore& a, const HighScore& b) { return a.score > b.score; });
	//remove excess scores
	if (m_HighScores.size() > s_MaxAmountOfHighScores)
	{
		m_HighScores.resize(s_MaxAmountOfHighScores);
	}
	SaveHighScores();
}

const std::vector<bm::HighScore>& bm::ScoreSystem::GetHighScores() const
{
	return m_HighScores;
}

void bm::ScoreSystem::LoadHighScores()
{
	m_HighScores.clear();

	std::ifstream file{ std::string(s_HighScoreFilePath) };
	if (!file.is_open())
		return;

	std::string line;
	while (std::getline(file, line, ';')) // split by ';'
	{
		if (line.empty())
			continue;

		std::istringstream inputStream{ line };
		std::string name{};
		int score{};

		if (std::getline(inputStream, name, ','))	//name
		{
			std::string scoreStr;
			if (std::getline(inputStream, scoreStr))	//score
			{
				try {
					score = std::stoi(scoreStr);
				}
				catch (...) {
					continue;
				}
			}
			else
			{
				continue;
			}
			m_HighScores.push_back({ name, score });
		}

		if (m_HighScores.size() >= s_MaxAmountOfHighScores)
			break;
	}

	std::sort(m_HighScores.begin(), m_HighScores.end(),
		[](const HighScore& a, const HighScore& b) { return a.score > b.score; });
}

void bm::ScoreSystem::SaveHighScores()
{
	std::ofstream file{ std::string(s_HighScoreFilePath) };
	if (!file.is_open())
		return;
	for (const auto& hs : m_HighScores)
	{
		file << hs;
	}
}
