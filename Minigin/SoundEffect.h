#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <string>
#include <memory>

#include "SoundDefines.h"

namespace dae
{
	class SoundEffect final
	{
	public:

		SoundEffect(const std::string& path);
		~SoundEffect();	//prevent compilation of default destructor in the header file. (which creates compiler errors due to the unique_ptr with its destructor)

		//defaulted in cpp
		SoundEffect(const SoundEffect&) = delete;
		SoundEffect& operator=(const SoundEffect&) = delete;
		SoundEffect(SoundEffect&&) noexcept; 
		SoundEffect& operator=(SoundEffect&&) noexcept; 

		void Load();
		bool IsLoaded() const;

		void SetVolume(sound_volume volume);

		void PlayEffect(int loops);

	private:

		class SDL_SoundEffectImpl;
		std::unique_ptr<SDL_SoundEffectImpl> m_pSDLSoundEffectImpl;
	};
}

#endif // !SOUNDEFFECT_H