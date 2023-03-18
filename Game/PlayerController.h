#pragma once
#include "Component.h"

class PhysicsBody;

class PlayerController final : public Component
{
public:
	explicit PlayerController(Entity* parent);

	void Initialize() override;
	void Update(float deltaTime) override;

private:
	PhysicsBody* m_pPhysicsBody{ nullptr };
};
