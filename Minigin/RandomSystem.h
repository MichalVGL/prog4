#ifndef RANDOMSYSTEM_H
#define RANDOMSYSTEM_H

#include "IRandomSystem.h"

#include <random>

namespace dae
{
	class Default_RandomSystem : public IRandomSystem
	{
	public:
		Default_RandomSystem();
		~Default_RandomSystem() override = default;

		float GetRandomFloat(float min = 0.f, float max = 1.f) override;
		int GetRandomInt(int min, int max) override; //inclusive range
		bool GetRandomBool(float trueChance = 0.5f) override;

	private:
		std::random_device m_RandomDevice;
		std::mt19937 m_Engine;
	};
}

#endif // !RANDOMSYSTEM_H