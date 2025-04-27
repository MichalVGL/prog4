#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <chrono>
#include <iostream>
#include <thread>

#include <filesystem>

#include "Minigin.h"
#include "DaeTime.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "ServiceLocator.h"
#include "Sound.h"

int dae::Minigin::m_MsPerFrame{ 16 };	//+-60 fps
float dae::Minigin::m_SecondsPerFixedUpdate{ 0.02f };

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Minigin",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,						//640,	//base settings
		480,						//480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

	//ServiceLocator::RegisterSoundSystem(std::make_unique<Null_SoundSystem>());
	ServiceLocator::RegisterSoundSystem(std::make_unique<Logger_SoundSystem>(
		std::make_unique<SDL_SoundSystem>(dataPath)));
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();
	dae::fixedDeltaTime = m_SecondsPerFixedUpdate;

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	sceneManager.Start();

	bool doContinue{ true };
	std::chrono::steady_clock::time_point lastTime{ std::chrono::high_resolution_clock::now() };
	std::chrono::steady_clock::time_point currentTime{};
	float lag{ 0.f };
	while (doContinue)
	{
		currentTime = std::chrono::high_resolution_clock::now();
		dae::deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		
		lastTime = currentTime;
		lag += dae::deltaTime;

		doContinue = input.ProcessInput();

		while (lag >= m_SecondsPerFixedUpdate)
		{
			sceneManager.FixedUpdate(m_SecondsPerFixedUpdate);
			lag -= m_SecondsPerFixedUpdate;
		}
		sceneManager.Update(dae::deltaTime);
		sceneManager.LateUpdate(dae::deltaTime);

		renderer.Render();

		std::this_thread::sleep_for(currentTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now());
	}
}
