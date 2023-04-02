#pragma once

#include "Scene.h"

class Entity;

class LevelScene final : public Scene
{
public:
	explicit LevelScene();

	void InitializeScene() override;
	void UpdateScene(float deltaTime) override;
	void DrawScene() const override;

private:
	Entity* m_pPlayer{};
	Entity* m_pObstacle{};
	Entity* m_pObstacle2{};

	Entity* m_pTestEnemy{};

	Entity* m_pTestLadder{};

	void CreatePlayer();
};

