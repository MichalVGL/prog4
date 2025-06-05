#ifndef SERVICELOCATOR_H  
#define SERVICELOCATOR_H  

#include <memory>  

#include "ISoundSystem.h"  
#include "ITextureSystem.h"
#include "IRenderSystem.h"
#include "IFontSystem.h"
#include "IRandomSystem.h"

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

	private:

		static std::unique_ptr<ISoundSystem> m_pSoundSystem;

		static std::unique_ptr<ITextureSystem> m_pTextureSystem;

		static std::unique_ptr<IRenderSystem> m_pRenderSystem;

		static std::unique_ptr<IFontSystem> m_pFontSystem;

		static std::unique_ptr<IRandomSystem> m_pRandomSystem;
	};
}

#endif // !SERVICELOCATOR_H
