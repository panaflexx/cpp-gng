#include "base.h"

#include "InputHandler.h"

void InputHandler::AddKey(const std::string& inputName, SDL_Scancode scancode)
{
	m_KeyMap[inputName] = scancode;
}

bool InputHandler::GetKeyDown(const std::string& key)
{
	return m_KeyDown[m_KeyMap[key]];
}

bool InputHandler::GetKeyPressed(const std::string& key)
{
	return m_KeyPressed[m_KeyMap[key]];
}

bool InputHandler::GetKeyUp(const std::string& key)
{
	return m_KeyUp[m_KeyMap[key]];
}

int InputHandler::GetAxis(const std::string& negativeKey, const std::string& positiveKey)
{
	if (GetKeyPressed(negativeKey)) return -1;
	if (GetKeyPressed(positiveKey)) return 1;

	return 0;
}

void InputHandler::Update()
{
	// Keyboard
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	for (std::pair<std::string, SDL_Scancode> inputPair : m_KeyMap)
	{
		const bool currentlyPressed = state[inputPair.second];
		const bool pressedLastFrame = m_PressedLastFrame[inputPair.second];

		// reset all values so we can set them for this frame
		m_KeyDown[inputPair.second] = false;
		m_KeyPressed[inputPair.second] = false;
		m_KeyUp[inputPair.second] = false;

		if (currentlyPressed && !pressedLastFrame)
		{
			m_KeyDown[inputPair.second] = true;
		}
		else if (currentlyPressed && pressedLastFrame)
		{
			m_KeyPressed[inputPair.second] = true;
		}
		else if (!currentlyPressed && pressedLastFrame)
		{
			m_KeyUp[inputPair.second] = true;
		}

		m_PressedLastFrame[inputPair.second] = currentlyPressed;
	}
}
