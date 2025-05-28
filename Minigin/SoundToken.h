#ifndef SOUNDTOKEN_H
#define SOUNDTOKEN_H

#include "SoundDefines.h"
#include "ISoundSystem.h"
#include "SoundEntry.h"
#include "ServiceLocator.h"

namespace dae
{
	class SoundToken final
	{
	public:
		SoundToken(const SoundEntry& entry);

		~SoundToken();

		SoundToken(const SoundToken&) = delete;
		SoundToken& operator=(const SoundToken&) = delete;
		SoundToken(SoundToken&&) = delete;
		SoundToken& operator=(SoundToken&&) = delete;

		void Play(sound_volume volume = 1.f, sound_loops loops = 0u);
		sound_id GetId() const;
		std::string_view GetPath() const;

	private:

		const SoundEntry& m_SoundEntry;
		ISoundSystem* m_pInitSoundSystem{ &ServiceLocator::GetSoundSystem() };
	};
}

#endif // !SOUNDTOKEN_H