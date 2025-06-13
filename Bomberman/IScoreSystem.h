#ifndef ISCORESYSTEM
#define ISCORESYSTEM

#include <string>
#include <fstream>
#include <vector>

namespace bm
{
	struct HighScore
	{
		std::string name;
		int score;

		//for file saving 
		friend std::ostream& operator<<(std::ostream& os, const HighScore& hs)
		{
			os << hs.name << ',' << hs.score << ';';
			return os;
		}
	};

	class IScoreSystem
	{
	public:
		virtual ~IScoreSystem() = default;

		virtual int GetScore() const = 0;

		virtual void AddScore(int amount) = 0;
		virtual void ResetScore() = 0;
		virtual void SetScore(int score) = 0;

		virtual bool IsHighScore() const = 0;
		virtual void AddHighScore(std::string name) = 0;

		virtual const std::vector<HighScore>& GetHighScores() const = 0;
	};
}

#endif // !ISCORESYSTEM

