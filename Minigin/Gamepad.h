#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <memory>

namespace dae
{
	class Gamepad final
	{
	public:

		explicit Gamepad(int id);
		~Gamepad();

		Gamepad() = delete;
		Gamepad(const Gamepad& other) = delete;
		Gamepad(Gamepad&& other) noexcept;
		Gamepad& operator=(const Gamepad& other) = delete;
		Gamepad& operator=(Gamepad&& other) noexcept;

		void UpdateInput();

		bool IsButtonUp(uint16_t button) const;
		bool IsButtonDown(uint16_t button) const;
		bool IsButtonPressed(uint16_t button) const;

		bool IsConnected() const;
		static bool IsValidGamepadButton(uint16_t button);

	private:

		class XinputImpl;
		std::unique_ptr<XinputImpl> m_pXinputImpl;
	};
}

#endif // GAMEPAD_H