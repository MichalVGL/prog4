#pragma once
#include <memory>

class Gamepad final
{
public:

	explicit Gamepad(int id);
	~Gamepad();

	Gamepad() = delete;
	Gamepad(const Gamepad& other)				= delete;
	Gamepad(Gamepad&& other) noexcept;
	Gamepad& operator=(const Gamepad& other)	= delete;
	Gamepad& operator=(Gamepad&& other) noexcept;

	void UpdateInput();

	bool IsButtonUp(uint8_t button);
	bool IsButtonDown(uint8_t button);
	bool IsButtonPressed(uint8_t button);

	bool IsConnected();
	static bool IsValidGamepadButton(uint8_t button);

private:

	class XinputImpl;
	std::unique_ptr<XinputImpl> m_XinputImpl_Uptr;
};

