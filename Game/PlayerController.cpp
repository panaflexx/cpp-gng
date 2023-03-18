#include "pch.h"
#include "PlayerController.h"

#include <cassert>

#include "Collider.h"
#include "Entity.h"
#include "InputHandler.h"
#include "PhysicsBody.h"
#include "PhysicsHandler.h"
#include "Transform.h"
#include "utils.h"

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
}

void PlayerController::Update(float deltaTime)
{
	// Apply gravity
	m_pPhysicsBody->AddVelocity(Vector2f(0, -50.f * deltaTime));

	const Vector2f bottomLeft{ m_pTransform->GetPosition() + Vector2f(1.f, -0.5f)};
	const Vector2f bottomRight{ bottomLeft + Vector2f(14, 0) };

	const std::pair<bool, Collider*> result{ GetPhysicsHandler()->Linecast(bottomLeft, bottomRight) };
	if(result.first)
	{
		m_pPhysicsBody->SetYVelocity(0);
	}

	if(GetInputHandler()->GetKeyPressed("test"))
	{
		m_pPhysicsBody->SetYVelocity(20);
	}
}

void PlayerController::Draw() const
{
	const Vector2f bottomLeft{ m_pTransform->GetPosition() + Vector2f(1.f, -0.5f) };
	const Vector2f bottomRight{ bottomLeft + Vector2f(14, 0) };

	utils::DrawLine(bottomLeft.ToPoint2f(), bottomRight.ToPoint2f());
}
