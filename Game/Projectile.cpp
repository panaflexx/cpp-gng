#include "pch.h"
#include "Projectile.h"

#include <cassert>

#include "Entity.h"
#include "Renderer.h"
#include "Transform.h"

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
}

void Projectile::OnCollisionEnter(Collider* other, float deltaTime)
{
	if (m_Type == Type::enemy && other->CompareTag("Player"))
	{
		// Damage player
	}
	else if (m_Type == Type::player && other->CompareTag("Enemy"))
	{
		// Damage other (enemy)
	}
}
