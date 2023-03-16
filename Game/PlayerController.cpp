#include "pch.h"
#include "PlayerController.h"

#include <cassert>

#include "Entity.h"
#include "PhysicsBody.h"

PlayerController::PlayerController(Entity* parent)
	: Component(parent)
{
}

void PlayerController::Initialize()
{
	m_pPhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_pPhysicsBody != nullptr && "Entity has renderer component but not physics body component");
}

void PlayerController::Update(float deltaTime)
{
	m_pPhysicsBody->AddVelocity(Vector2f(0, -50.f * deltaTime));
}
