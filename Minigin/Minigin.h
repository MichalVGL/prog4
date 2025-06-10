#ifndef MINIGIN_H
#define MINIGIN_H

#include <string>
#include <functional>
#include <memory>

#include "RenderUtils.h"
#include "Scene.h"

namespace dae
{
	class Minigin final
	{
	public:
		explicit Minigin(const std::string& dataPath, const Window& window);
		~Minigin();
		void Run(std::unique_ptr<Scene>&& startScene);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		static int m_MsPerFrame;
		static float m_SecondsPerFixedUpdate;
	};
}

#endif // MINIGIN_H