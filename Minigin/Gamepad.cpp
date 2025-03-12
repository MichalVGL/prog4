
//todo make sure to include lead and mean, lookup reason (decreases compile time)
#include <cassert>
#include <Windows.h>
#include <Xinput.h>
#include "Gamepad.h"

//===============================
// Xinput implementation
//===============================

class Gamepad::XinputImpl final
{
public:

	explicit XinputImpl(int id);
	XinputImpl() = delete;

	void UpdateInputImpl();

	bool IsButtonUp(uint8_t button) const;
	bool IsButtonDown(uint8_t button) const;
	bool IsButtonPressed(uint8_t button) const;

	bool IsConnected() const;
	static bool IsValidGamepadButton(uint8_t button);

private:

	int m_ID;
	bool m_IsConnected;

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;

	WORD m_Buttons;
	WORD m_PressedButtons;
	WORD m_ReleasedButtons;
};

Gamepad::XinputImpl::XinputImpl(int id)
	: m_ID{ id }
	, m_IsConnected{}
	, m_CurrentState{}
	, m_PreviousState{}
	, m_Buttons{}
	, m_PressedButtons{}
	, m_ReleasedButtons{}
{
	assert(id < XUSER_MAX_COUNT && id >= 0
		&& "Given GamePad ID is invalid");
}

void Gamepad::XinputImpl::UpdateInputImpl()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(m_ID, &m_CurrentState);

	if (result == ERROR_SUCCESS)
	{
		m_IsConnected = true;
		m_Buttons = m_CurrentState.Gamepad.wButtons;
		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_PressedButtons = buttonChanges & m_Buttons;
		m_ReleasedButtons = buttonChanges & (~m_Buttons);
	}
	else if (result == ERROR_DEVICE_NOT_CONNECTED
		|| result == ERROR_DEVICE_NOT_AVAILABLE)
	{
		m_IsConnected = false;
	}
}

bool Gamepad::XinputImpl::IsButtonUp(uint8_t button) const
{
	return m_ReleasedButtons & static_cast<WORD>(button);
}

bool Gamepad::XinputImpl::IsButtonDown(uint8_t button) const
{
	return m_PressedButtons & static_cast<WORD>(button);
}

bool Gamepad::XinputImpl::IsButtonPressed(uint8_t button) const
{
	return m_Buttons & static_cast<WORD>(button);
}

bool Gamepad::XinputImpl::IsConnected() const
{
	return m_IsConnected;
}

bool Gamepad::XinputImpl::IsValidGamepadButton(uint8_t button)
{
	constexpr WORD validButtons =
		XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_DOWN |
		XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT |
		XINPUT_GAMEPAD_START | XINPUT_GAMEPAD_BACK |
		XINPUT_GAMEPAD_LEFT_THUMB | XINPUT_GAMEPAD_RIGHT_THUMB |
		XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER |
		XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y;

	return (static_cast<WORD>(button) & validButtons)						// Is it a valid button
		&& !(static_cast<WORD>(button) & (static_cast<WORD>(button) - 1));	// Only one bit is set
}

//===============================
// Base Gamepad
//===============================

Gamepad::Gamepad(int id)
	:m_XinputImpl_Uptr{std::make_unique<XinputImpl>(id)}
{
}

Gamepad::~Gamepad() = default;
Gamepad::Gamepad(Gamepad&& other) noexcept = default;
Gamepad& Gamepad::operator=(Gamepad&& other) noexcept = default;

void Gamepad::UpdateInput()
{
	m_XinputImpl_Uptr->UpdateInputImpl();
}

bool Gamepad::IsButtonUp(uint8_t button) const
{
	return m_XinputImpl_Uptr->IsButtonUp(button);
}

bool Gamepad::IsButtonDown(uint8_t button) const
{
	return m_XinputImpl_Uptr->IsButtonDown(button);
}

bool Gamepad::IsButtonPressed(uint8_t button) const
{
	return m_XinputImpl_Uptr->IsButtonPressed(button);
}

bool Gamepad::IsConnected() const
{
	return m_XinputImpl_Uptr->IsConnected();
}

bool Gamepad::IsValidGamepadButton(uint8_t button)
{
	return XinputImpl::IsValidGamepadButton(button);
}

