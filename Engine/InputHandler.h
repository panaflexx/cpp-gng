#pragma once
#include <SDL.h>
#include <unordered_map>
#include <map>

class InputHandler final
{
public:
	void AddKey(const std::string& inputName, SDL_Scancode scancode);

	bool GetKeyDown(const std::string& key);
	bool GetKeyPressed(const std::string& key);
	bool GetKeyUp(const std::string& key);
	int GetAxis(const std::string& negativeKey, const std::string& positiveKey);

	void Update();

private:
	std::map<std::string, SDL_Scancode> m_KeyMap;

	std::unordered_map<SDL_Scancode, bool> m_KeyDown;
	std::unordered_map<SDL_Scancode, bool> m_KeyPressed;
	std::unordered_map<SDL_Scancode, bool> m_KeyUp;

	std::unordered_map<SDL_Scancode, bool> m_PressedLastFrame;
};
