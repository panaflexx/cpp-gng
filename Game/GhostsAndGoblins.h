#pragma once
#include "Game.h"
#include "LevelScene.h"

class GhostsAndGoblins final : public Game
{
public:
	explicit GhostsAndGoblins(const Window& window)
		: Game{ window, new LevelScene() }
	{
	}

	void UpdateGame(float deltaTime) override;
	void DrawGame() const override;
};

