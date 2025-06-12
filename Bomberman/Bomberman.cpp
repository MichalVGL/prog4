
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
#include <memory>

#include <Minigin.h>
#include <Scene.h>
#include <EngineComponents.h>
#include <filesystem>
#include <ServiceLocator.h>
#include <Utils.h>
#include <Command.h>
#include <InputManager.h>
#include <Keyboard.h>

#include "BMGameDefines.h"
#include "BMComponents.h"
#include "ObjectConstructions.h"
#include "BMServiceLocator.h"
#include "TileSystem.h"
#include "PlayerController.h"
#include "AIController.h"
#include "TestScene.h"
#include "LevelScene.h"

std::filesystem::path GetDataPath()
{
	// Visual studio path
	std::filesystem::path vsPath = "../" DATA_FOLDER_PATH;
	if (std::filesystem::exists(vsPath))
		return vsPath;

	// Exe path
	std::filesystem::path exePath = DATA_FOLDER_PATH;
	if (std::filesystem::exists(exePath))
		return exePath;

	std::cout << "Data folder not found.\n";
	throw std::runtime_error("Data folder not found.");
}

class MuteCommand final : public dae::Command
{
public:
	// Inherited via Command
	void Execute() override
	{
		auto& soundSystem = dae::ServiceLocator::GetSoundSystem();
		if (m_Muted)
		{
			soundSystem.SetGlobalVolume(bm::SOUNDVOLUME);
			m_Muted = false;
		}
		else
		{
			soundSystem.SetGlobalVolume(0.f);
			m_Muted = true;
		}
	}
private:

	bool m_Muted{ false };
};

int main(int, char* []) {

	dae::Window window{ .title = "Bomberman", .w = bm::WINDOW_BASESIZE.x, .h = bm::WINDOW_BASESIZE.y, .renderScale = bm::RENDER_SCALE };

	dae::Minigin engine(GetDataPath().string(), window);
	dae::ServiceLocator::GetSoundSystem().SetGlobalVolume(bm::SOUNDVOLUME);
	//todo setup f2 here
	auto& inputManager = dae::InputManager::GetInstance();
	auto binding = std::make_unique<dae::KeyboardBinding>(inputManager.CreateBinding(SDL_SCANCODE_F2, dae::KeyState::down,
		std::make_unique<MuteCommand>()));
	inputManager.RegisterBinding(binding.get());
	engine.Run(std::make_unique<bm::LevelScene>(3));
	return 0;
}