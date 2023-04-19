#include "base.h"
#include "pch.h"
#include "ZombieCollider.h"

#include <cassert>

#include "Entity.h"
#include "LadderCollider.h"
#include "PlayerController.h"
#include "Transform.h"

ZombieCollider::ZombieCollider(Entity* pParent, std::vector<Vector2f> pVector)
	: Collider(pParent, pVector)
{
}

void ZombieCollider::Initialize()
{
	Collider::Initialize();

	m_Zombie = m_pParent->GetComponent<Zombie>();
	assert(m_Zombie != nullptr && "Entity has ZombieCollider component but no Zombie component");
}

void ZombieCollider::OnCollisionEnter(Collider* other, float deltaTime, Vector2f normal)
{
	if(other->CompareTag("foreground"))
	{
        DPRINTF("ZombieCollider::OnCollisionEnter: foreground\n");
	} else if(other->CompareTag("gravestone"))
    {
		if(normal.y < 0)
			m_Zombie->Event("gravestone:on");
    }
}

void ZombieCollider::OnCollisionUpdate(Collider* other, float deltaTime, Vector2f normal)
{
	if(other->CompareTag("foreground"))
	{
        DPRINTF("ZombieCollider::OnCollisionUpdate: foreground\n");
		if(normal.y < 0)
			m_Zombie->Event("grounded:on");
	}
}

void ZombieCollider::OnCollisionExit(Collider* other, float deltaTime, Vector2f normal)
{
	if(other->CompareTag("foreground"))
	{
        DPRINTF("ZombieCollider::OnCollisionExit: foreground\n");
		//m_Zombie->m_IsGrounded = false;
        m_Zombie->Event("grounded:off");
	}
	if(other->CompareTag("gravestone"))
    {
        m_Zombie->Event("gravestone:off");
    }
}

