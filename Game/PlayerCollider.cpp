#include "pch.h"
#include "PlayerCollider.h"

#include <cassert>

#include "Entity.h"
#include "PlayerController.h"
#include "Transform.h"

PlayerCollider::PlayerCollider(Entity* pParent)
	: Collider(pParent, std::vector<Vector2f>{})
{
}

void PlayerCollider::Initialize()
{
	Collider::Initialize();

	m_pPlayerController = m_pParent->GetComponent<PlayerController>();
	assert(m_pPlayerController != nullptr && "Entity has PlayerCollider component but no PlayerController component");
}

void PlayerCollider::OnCollisionEnter(Collider* other, float deltaTime)
{
	if(other->CompareTag("Enemy"))
	{
		std::cout << "Oh no! Player collided with an enemy! :(" << std::endl;
	}

	if(other->CompareTag("Ladder"))
	{
		m_IsTouchingLadder = true;
		m_CurrentLadderX = other->GetParent()->GetComponent<Transform>()->GetPosition().x;
	}
}

void PlayerCollider::OnCollisionExit(Collider* other, float deltaTime)
{
	if (other->CompareTag("Ladder"))
	{
		m_IsTouchingLadder = false;
		m_CurrentLadderX = 0;
	}
}

bool PlayerCollider::IsTouchingLadder() const
{
	return m_IsTouchingLadder;
}

float PlayerCollider::GetCurrentLadderX() const
{
	return m_CurrentLadderX;
}

