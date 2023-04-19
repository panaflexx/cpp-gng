#include "pch.h"
#include "Zombie.h"

#include <cassert>

#include "AnimatorRenderer.h"
#include "Entity.h"
#include "EntityKeeper.h"
#include "LevelScene.h"
#include "PhysicsBody.h"
#include "Transform.h"
#include "Collider.h"

Zombie::Zombie(Entity* pParent, LevelScene* pLevelScene)
	: Component(pParent)
	, m_pLevelScene{ pLevelScene }
{
}

void Zombie::Initialize()
{
	m_pPlayer = m_pLevelScene->GetPlayer()->GetComponent<Transform>();

	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has Zombie component but no Transform component");
	m_pCollider = m_pParent->GetComponent<Collider>();
	assert(m_pCollider != nullptr && "Entity has Zombie component but no Collider component");
	m_pPhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_pPhysicsBody != nullptr && "Entity has Zombie component but no PhysicsBody component");
	m_pAnimator = m_pParent->GetComponent<AnimatorRenderer>();
	assert(m_pAnimator != nullptr && "Entity has Zombie component but no AnimatorRenderer component");
}

void Zombie::Update(float deltaTime)
{
	if (!m_IsDead)
	{
		m_pAnimator->SetFlipX(m_pPhysicsBody->GetVelocity().x < 0);

		const bool isRightOfPlayer{ m_pTransform->GetPosition().x > m_pPlayer->GetPosition().x };
		const float directionTowardsPlayer{ isRightOfPlayer ? -1.f : 1.f };

		m_pPhysicsBody->SetXVelocity(directionTowardsPlayer * m_WalkSpeed);
		if(!m_IsGrounded) {
			m_pPhysicsBody->AddVelocity(Vector2f(0, -(m_GravityScale * (deltaTime))));
		}

		return;
	}

	if (m_CurrentDeathTime > 0.f)
	{
		m_CurrentDeathTime -= deltaTime;
	}
	else
	{
		GetParent()->SetActive(false);
	}
}

void Zombie::Damage()
{
	m_pAnimator->SetParameter("isDead", true);

	m_pPhysicsBody->SetXVelocity(0);
	m_pPhysicsBody->SetYVelocity(0);

	m_pCollider->SetEnabled(false);

	m_CurrentDeathTime = m_DeathTime;
	m_IsDead = true;
}

void Zombie::Event(std::string name)
{
	// Basic events to handle gravity
	if(name == "foreground" || name == "grounded:on")
		m_IsGrounded = true;
	if(name == "grounded:off")
		m_IsGrounded = true;
}

void Zombie::Reset()
{
	m_IsDead = false;
	m_pAnimator->SetState("walk");
	m_pAnimator->SetParameter("isDead", false);

	m_pCollider->SetEnabled(true);
}
