#ifndef SERVICELOCATOR_H  
#define SERVICELOCATOR_H  

#include <memory>  

#include "ISoundSystem.h"  
#include "ITextureSystem.h"
#include "IRenderSystem.h"
#include "IFontSystem.h"
#include "IRandomSystem.h"
#include "ICameraSystem.h"
#include "ISceneSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:

		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& pSoundSystem);
		static ISoundSystem& GetSoundSystem();

		static void RegisterTextureSystem(std::unique_ptr<ITextureSystem>&& pTextureSystem);
		static ITextureSystem& GetTextureSystem();

		static void RegisterRenderSystem(std::unique_ptr<IRenderSystem>&& pRenderSystem);
		static IRenderSystem& GetRenderSystem();

		static void RegisterFontSystem(std::unique_ptr<IFontSystem>&& pFontSystem);
		static IFontSystem& GetFontSystem();

		static void RegisterRandomSystem(std::unique_ptr<IRandomSystem>&& pRandomSystem);
		static IRandomSystem& GetRandomSystem();

		static void RegisterCameraSystem(std::unique_ptr<ICameraSystem>&& pCameraSystem);
		static ICameraSystem& GetCameraSystem();

		static void RegisterSceneSystem(std::unique_ptr<ISceneSystem>&& pSceneSystem);
		static ISceneSystem& GetSceneSystem();

	private:

		static std::unique_ptr<ISoundSystem> s_pSoundSystem;

		static std::unique_ptr<ITextureSystem> s_pTextureSystem;

		static std::unique_ptr<IRenderSystem> s_pRenderSystem;

		static std::unique_ptr<IFontSystem> s_pFontSystem;

		static std::unique_ptr<IRandomSystem> s_pRandomSystem;

		static std::unique_ptr<ICameraSystem> s_pCameraSystem;

		static std::unique_ptr<ISceneSystem> s_pSceneSystem;
	};
}

#endif // !SERVICELOCATOR_H
