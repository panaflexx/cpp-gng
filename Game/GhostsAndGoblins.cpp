#include "pch.h"
#include "GhostsAndGoblins.h"

#include "InputHandler.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins(const Window& window)
	: Game(window, new LevelScene())
{
	m_pInputHandler->AddKey("left", SDL_SCANCODE_LEFT);
	m_pInputHandler->AddKey("right", SDL_SCANCODE_RIGHT);
	m_pInputHandler->AddKey("up", SDL_SCANCODE_UP);
	m_pInputHandler->AddKey("down", SDL_SCANCODE_DOWN);
	m_pInputHandler->AddKey("jump", SDL_SCANCODE_J);
	m_pInputHandler->AddKey("fire", SDL_SCANCODE_K);
	m_pInputHandler->AddKey("jump", SDL_SCANCODE_LCTRL);
	m_pInputHandler->AddKey("fire", SDL_SCANCODE_LALT);

	m_pInputHandler->AddKey("info", SDL_SCANCODE_I);
	m_pInputHandler->AddKey("exit", SDL_SCANCODE_ESCAPE);
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}

void GhostsAndGoblins::DrawGame() const
{
}

