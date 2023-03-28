#pragma once
#include "Collider.h"

class AnimatorRenderer;
class PlayerController;

class PlayerCollider final : public Collider
{
public:
	explicit PlayerCollider(Entity* pParent);

	void Initialize() override;
	void OnCollisionEnter(Collider* other, float deltaTime) override;
	void OnCollisionExit(Collider* other, float deltaTime) override;

	bool IsTouchingLadder() const;
	float GetCurrentLadderX() const;
private:
	PlayerController* m_pPlayerController{ nullptr };

	bool m_IsTouchingLadder{ false };
	float m_CurrentLadderX{};
};
