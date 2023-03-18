#include "pch.h"
#include "GhostsAndGoblins.h"

#include "InputHandler.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins(const Window& window)
	: Game(window, new LevelScene())
{
	m_pInputHandler->AddKey("test", SDL_SCANCODE_SPACE);
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}

void GhostsAndGoblins::DrawGame() const
{
}
