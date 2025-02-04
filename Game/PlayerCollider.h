#pragma once
#include "Collider.h"

class LadderCollider;
class AnimatorRenderer;
class PlayerController;

class PlayerCollider final : public Collider
{
public:
	explicit PlayerCollider(Entity* pParent);

	void Initialize() override;
	void OnCollisionEnter(Collider* other, float deltaTime, Vector2f normal) override;
	void OnCollisionUpdate(Collider* other, float deltaTime, Vector2f normal) override;
	void OnCollisionExit(Collider* other, float deltaTime, Vector2f normal) override;

	bool IsTouchingLadder() const;
	LadderCollider* GetTouchedLadder() const;
private:
	PlayerController* m_pPlayerController{ nullptr };

	LadderCollider* m_pTouchedLadder{ nullptr };
};
