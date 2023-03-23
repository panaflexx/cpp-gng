#pragma once
#include "Collider.h"

class PlayerController;

class PlayerCollider final : public Collider
{
public:
	explicit PlayerCollider(Entity* pParent);

	void Initialize() override;
	void OnCollisionEnter(Collider* other, float deltaTime) override;
	void OnCollisionExit(Collider* other, float deltaTime) override;

private:
	PlayerController* m_pPlayerController{ nullptr };
};
