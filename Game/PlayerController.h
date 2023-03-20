#pragma once
#include "Component.h"

class AnimatorRenderer;
class Collider;
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
	Collider* m_pCollider{ nullptr };
	PhysicsBody* m_pPhysicsBody{ nullptr };
	AnimatorRenderer* m_pAnimator{ nullptr };

	bool m_IsGrounded{ false };
	bool m_IsCrouched{ false };
	int m_LookDir{ 1 };

	void UpdateMovement();
	void CheckGrounded(float deltaTime);
	void UpdateJumping() const;
	void UpdateShooting(float deltaTime);

	const float m_GravityScale{ 100.f };

	const float m_ColliderWidth{ 22.f };
	const float m_ColliderHeight{ 25.f };

	const float m_MovementSpeed{ 30.f };
	const float m_JumpForce{ 50.f };

	const float m_CrouchedHitboxHeightMultiplier{ 0.5f };

	const float m_ShootCooldown{ 0.5f };
	float m_CurrentShootCooldown{};

	const float m_ShootTime{ 0.1f };
	float m_CurrentShootTime{};

	bool m_IsShooting{ false };
};
