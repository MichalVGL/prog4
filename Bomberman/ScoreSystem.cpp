#include "ScoreSystem.h"

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <DaeFiles.h>

bm::Default_ScoreSystem::Default_ScoreSystem()
{
	LoadHighScores();
}

int bm::Default_ScoreSystem::GetScore() const
{
	return m_CurrentScore;
}

void bm::Default_ScoreSystem::AddScore(int amount)
{
	m_CurrentScore += amount;
}

void bm::Default_ScoreSystem::ResetScore()
{
	m_CurrentScore = 0;
}

void bm::Default_ScoreSystem::SetScore(int score)
{
	m_CurrentScore = score;
}

bool bm::Default_ScoreSystem::IsHighScore() const
{
	if (m_HighScores.size() < s_MaxAmountOfHighScores)
		return true; // unfilled high scores, so any score is a high score
	return m_CurrentScore > m_HighScores.back().score;
}

void bm::Default_ScoreSystem::AddHighScore(std::string name)
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

const std::vector<bm::HighScore>& bm::Default_ScoreSystem::GetHighScores() const
{
	return m_HighScores;
}

void bm::Default_ScoreSystem::LoadHighScores()
{
	m_HighScores.clear();

	auto fullPath = dae::dataPath / s_HighScoreFilePath;

	std::ifstream file{ fullPath };
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

void bm::Default_ScoreSystem::SaveHighScores()
{
	auto fullPath = dae::dataPath / s_HighScoreFilePath;
	std::ofstream file{ fullPath };
	if (!file.is_open())
		return;
	for (const auto& hs : m_HighScores)
	{
		file << hs;
	}
}