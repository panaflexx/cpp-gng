#pragma once
#include "Collider.h"
#include "Zombie.h"

class LadderCollider;
class AnimatorRenderer;
class PlayerController;

class ZombieCollider final : public Collider
{
public:
	explicit ZombieCollider(Entity* pParent, std::vector<Vector2f> pVector);

	void Initialize() override;
	void OnCollisionEnter(Collider* other, float deltaTime, Vector2f normal) override;
	void OnCollisionUpdate(Collider* other, float deltaTime, Vector2f normal) override;
	void OnCollisionExit(Collider* other, float deltaTime, Vector2f normal) override;

private:
	Zombie* m_Zombie{ nullptr };
};
