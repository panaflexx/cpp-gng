#pragma once
#include "Component.h"

class Transform;
class PhysicsBody;

class PlayerController final : public Component
{
public:
	explicit PlayerController(Entity* parent);

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	Transform* m_pTransform{ nullptr };
	PhysicsBody* m_pPhysicsBody{ nullptr };
};
