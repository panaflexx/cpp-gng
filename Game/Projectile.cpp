#include "pch.h"
#include "Projectile.h"

#include <cassert>

#include "Entity.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "Transform.h"
#include "Zombie.h"

Projectile::Projectile(Entity* pParent)
	: Collider(pParent, std::vector<Vector2f>(4), true)
	, m_Type{ Type::player }
{
}

void Projectile::Initialize()
{
	Collider::Initialize();

	m_pRenderer = m_pParent->GetComponent<Renderer>();
	assert(m_pRenderer != nullptr && "Entity has Projectile component but no Transform component");
}

void Projectile::Update(float deltaTime)
{
	m_pTransform->MovePosition(m_Velocity * deltaTime);
	RecalculateTransformedVertices();

	m_Lifetime += deltaTime;

	if(m_Lifetime > m_MaxLifetime)
	{
		GetParent()->SetActive(false);
	}
}

void Projectile::SetFireData(const FireData& data)
{
	m_Lifetime = 0;

	m_Type = data.type;
	m_pTransform->SetPosition(data.start);
	m_Velocity = data.velocity;

	m_BaseVertices = std::vector<Vector2f>{
		Vector2f(-data.width / 2, -data.height / 2),
		Vector2f(-data.width / 2, data.height / 2),
		Vector2f(data.width / 2, data.height / 2),
		Vector2f(data.width / 2, -data.height / 2),
	};

	m_pRenderer->SetFlipX(data.velocity.x < 0);
}

void Projectile::OnCollisionEnter(Collider* other, float deltaTime, Vector2f normal)
{
	if (m_Type == Type::enemy && other->CompareTag("Player"))
	{
		PlayerController* player{ other->GetParent()->GetComponent<PlayerController>() };
		player->Damage(m_pTransform->GetPosition());

		m_pParent->SetActive(false);
	}
	else if (m_Type == Type::player && other->CompareTag("Enemy"))
	{
		Zombie* pEnemy{ other->GetParent()->GetComponent<Zombie>() };
		pEnemy->Damage();

		m_pParent->SetActive(false);
	}
}
