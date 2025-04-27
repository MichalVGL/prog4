#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <memory>

#include "Singleton.h"

namespace dae
{
	class Keyboard final : public dae::Singleton<Keyboard>
	{
	public:

		Keyboard();
		~Keyboard();

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) noexcept = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) noexcept = delete;

		void UpdateInput();

		bool IsButtonUp(uint16_t key);
		bool IsButtonDown(uint16_t key);
		bool IsButtonPressed(uint16_t key);

	private:

		class SDLImpl;
		std::unique_ptr<SDLImpl> m_SDLImpl_Uptr;

	};
}

#endif // KEYBOARD_H