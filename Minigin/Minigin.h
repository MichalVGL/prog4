#pragma once
#include <string>
#include <functional>

//todo change push_back to emplace_back

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		static int m_MsPerFrame;
		static float m_SecondsPerFixedUpdate;
	};
}