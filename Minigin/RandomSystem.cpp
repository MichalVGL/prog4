#include "RandomSystem.h"

dae::Default_RandomSystem::Default_RandomSystem()
	:m_RandomDevice{}
	, m_Engine(m_RandomDevice())
{
}

float dae::Default_RandomSystem::GetRandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(m_Engine);
}

int dae::Default_RandomSystem::GetRandomInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(m_Engine);
}

bool dae::Default_RandomSystem::GetRandomBool(float trueChance)
{
	std::bernoulli_distribution dist(trueChance);
	return dist(m_Engine);
}
