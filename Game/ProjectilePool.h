#pragma once
#include "Projectile.h"

class LevelScene;

class ProjectilePool
{
public:
	explicit ProjectilePool(const LevelScene* pLevelScene);

	void FireProjectile(const Projectile::FireData& data) const;

private:
	std::vector<Projectile*> m_Projectiles;
};

