#include "pch.h"
#include "PlayerController.h"

#include <cassert>

#include "AnimatorRenderer.h"
#include "Collider.h"
#include "Entity.h"
#include "InputHandler.h"
#include "PhysicsBody.h"
#include "PhysicsHandler.h"
#include "Transform.h"
#include "utils.h"

class AnimatorRenderer;

PlayerController::PlayerController(Entity* parent)
	: Component(parent)
{
}

void PlayerController::Initialize()
{
	m_pPhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_pPhysicsBody != nullptr && "Entity has PlayerController component but not PhysicsBody component");
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has PlayerController component but no Transform component");
	m_pCollider = m_pParent->GetComponent<Collider>();
	assert(m_pCollider != nullptr && "Entity has PlayerController component but no Collider component");
	m_pAnimator = m_pParent->GetComponent<AnimatorRenderer>();
	assert(m_pAnimator != nullptr && "Entity has AnimatorRenderer component but no AnimatorRenderer component");

	m_pCollider->SetBaseVertices(std::vector<Vector2f>{
		Vector2f(-m_ColliderWidth / 2, -m_ColliderHeight / 2),
		Vector2f(-m_ColliderWidth / 2, m_ColliderHeight / 2),
		Vector2f(m_ColliderWidth / 2, m_ColliderHeight / 2),
		Vector2f(m_ColliderWidth / 2, -m_ColliderHeight / 2)
	});
}

void PlayerController::Update(float deltaTime)
{
	UpdateMovement();
	CheckGrounded(deltaTime);

	if (!m_IsGrounded)
	{
		// Apply gravity if we're not grounded
		m_pPhysicsBody->AddVelocity(Vector2f(0, -m_GravityScale * deltaTime));
	}
	else
	{
		// Reset velocity, otherwise gravity pulls into the ground
		// if we'd reset to 0 the ground would never register collision
		m_pPhysicsBody->SetYVelocity(-5);
	}

	UpdateJumping();
	UpdateShooting();
}

void PlayerController::Draw() const
{
	const Vector2f bottomLeft{ m_pTransform->GetPosition() + Vector2f(-m_ColliderWidth / 2 + 1, -m_ColliderHeight / 2 - 0.5f) };
	const Vector2f bottomRight{ bottomLeft + Vector2f(m_ColliderWidth - 2, 0) };

	utils::SetColor(Color4f(0, 1, 0, 1));
	utils::DrawLine(bottomLeft.ToPoint2f(), bottomRight.ToPoint2f());
}

void PlayerController::UpdateMovement()
{
	int moveDir{ GetInputHandler()->GetAxis("left", "right") };

	if (moveDir != 0)
	{
		m_LookDir = moveDir;
	}

	m_pAnimator->SetFlipX(m_LookDir != 1);
	m_pAnimator->SetParameter("moveDir", moveDir);

	// Crouching
	m_IsCrouched = GetInputHandler()->GetKeyPressed("crouch") && m_IsGrounded;
	m_pAnimator->SetParameter("isCrouched", m_IsCrouched);

	if(m_IsCrouched)
	{
		moveDir = 0;
		m_pCollider->GetBaseVertices()[1].y = -m_ColliderHeight / 2 + m_ColliderHeight * m_CrouchedHitboxHeightMultiplier;
		m_pCollider->GetBaseVertices()[2].y = -m_ColliderHeight / 2 + m_ColliderHeight * m_CrouchedHitboxHeightMultiplier;
	}
	else
	{
		m_pCollider->GetBaseVertices()[1].y = m_ColliderHeight / 2;
		m_pCollider->GetBaseVertices()[2].y = m_ColliderHeight / 2;
	}

	// Disallow changing X velocity while jumping
	if(m_IsGrounded)
	{
		m_pPhysicsBody->SetXVelocity(m_MovementSpeed * static_cast<float>(moveDir));
	}
}

void PlayerController::CheckGrounded(float deltaTime)
{
	// Grounded check
	const Vector2f bottomLeft{ m_pTransform->GetPosition() + Vector2f(-m_ColliderWidth / 2 + 1, -m_ColliderHeight / 2 - 0.5f) };
	const Vector2f bottomRight{ bottomLeft + Vector2f(m_ColliderWidth - 2, 0) };

	const std::pair<bool, Collider*> result{ GetPhysicsHandler()->Linecast(bottomLeft, bottomRight) };

	m_IsGrounded = result.first;
	m_pAnimator->SetParameter("isGrounded", m_IsGrounded);
}

void PlayerController::UpdateJumping() const
{
	if (m_IsGrounded && GetInputHandler()->GetKeyDown("jump"))
	{
		m_pPhysicsBody->SetYVelocity(m_JumpForce);
		// Move out of ground so next frame isn't considered grounded instantly
		m_pTransform->MovePosition(Vector2f(0, 1));
	}
}

void PlayerController::UpdateShooting()
{
}
