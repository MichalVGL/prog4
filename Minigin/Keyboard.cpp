#include <algorithm>
#include <functional>
#include <array>
#include <SDL.h>
#include <cassert>
#include "Keyboard.h"

#include "Time.h"

//===============================
// SDL implementation
//===============================

class Keyboard::SDLImpl final
{
public:

	void UpdateInput();

	bool IsButtonUp(uint16_t key);
	bool IsButtonDown(uint16_t key);
	bool IsButtonPressed(uint16_t key);

private: 

	std::array<Uint8, SDL_NUM_SCANCODES> m_CurrentKeys{};
	std::array<Uint8, SDL_NUM_SCANCODES> m_PreviousKeys{};
	std::array<Uint8, SDL_NUM_SCANCODES> m_ChangedKeys{};
	std::array<Uint8, SDL_NUM_SCANCODES> m_PressedKeys{};
	std::array<Uint8, SDL_NUM_SCANCODES> m_ReleasedKeys{};
};

void Keyboard::SDLImpl::UpdateInput()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	m_PreviousKeys = m_CurrentKeys;
	std::copy(pStates, pStates + SDL_NUM_SCANCODES, m_CurrentKeys.begin());

	std::transform(m_CurrentKeys.begin(), m_CurrentKeys.end(), m_PreviousKeys.begin(), m_ChangedKeys.begin(), std::bit_xor<Uint8>());	//current ^ previous
	std::transform(m_ChangedKeys.begin(), m_ChangedKeys.end(), m_CurrentKeys.begin(), m_PressedKeys.begin(), std::bit_and<Uint8>());	//changed & current
	std::transform(m_ChangedKeys.begin(), m_ChangedKeys.end(), m_CurrentKeys.begin(), m_ReleasedKeys.begin(),							//changed & ~current
		[](Uint8 changed, Uint8 current) { return static_cast<Uint8>(changed & ~current); });
}

bool Keyboard::SDLImpl::IsButtonUp(uint16_t key)
{
	assert(key < SDL_NUM_SCANCODES && "Key out of bounds");
	return m_ReleasedKeys.at(static_cast<SDL_Scancode>(key));
}

bool Keyboard::SDLImpl::IsButtonDown(uint16_t key)
{
	assert(key < SDL_NUM_SCANCODES && "Key out of bounds");
	return m_PressedKeys.at(static_cast<SDL_Scancode>(key));
}

bool Keyboard::SDLImpl::IsButtonPressed(uint16_t key)
{
	
	assert(key < SDL_NUM_SCANCODES && "Key out of bounds");
	return m_CurrentKeys.at(static_cast<SDL_Scancode>(key));
}

//===============================
// Base Keyboard
//===============================

Keyboard::Keyboard()
	: m_SDLImpl_Uptr{std::make_unique<SDLImpl>()}
{
}

Keyboard::~Keyboard() = default;

void Keyboard::UpdateInput()
{
	m_SDLImpl_Uptr->UpdateInput();
}

bool Keyboard::IsButtonUp(uint16_t key)
{
	return m_SDLImpl_Uptr->IsButtonUp(key);
}

bool Keyboard::IsButtonDown(uint16_t key)
{
	return m_SDLImpl_Uptr->IsButtonDown(key);
}

bool Keyboard::IsButtonPressed(uint16_t key)
{
	return m_SDLImpl_Uptr->IsButtonPressed(key);
}

