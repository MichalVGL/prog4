#ifndef IRANDOMSYSTEM
#define IRANDOMSYSTEM

namespace dae
{
	class IRandomSystem
	{
	public:
		virtual ~IRandomSystem() = default;

		virtual float GetRandomFloat(float min = 0.f, float max = 1.f) = 0;

		virtual int GetRandomInt(int min, int max) = 0;	//inclusive range

		virtual bool GetRandomBool(float trueChance = 0.5f) = 0;
	};
}
#endif // !IRANDOMSYSTEM