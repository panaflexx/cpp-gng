#pragma once

#include "Scene.h"
#include "Vector2f.h"

class ProjectilePool;
class Transform;
class Entity;

class LevelScene final : public Scene
{
public:
	void InitializeScene() override;
	void CleanupScene() override;
	void UpdateScene(float deltaTime) override;
	void DrawScene() const override;

	ProjectilePool* GetProjectilePool() const;

private:
	ProjectilePool* m_pProjectilePool{};

	Entity* m_pPlayer{};

	Vector2f m_LevelSize{};
	Transform* m_pBackgroundTransform{};

	void CreatePlayer();
	void CreateLevel();
};

