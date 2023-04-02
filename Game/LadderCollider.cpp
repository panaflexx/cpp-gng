#include "pch.h"
#include "LadderCollider.h"

#include <cassert>

#include "Entity.h"
#include "PhysicsHandler.h"
#include "Scene.h"
#include "Transform.h"

LadderCollider::LadderCollider(Entity* pParent, const std::vector<Vector2f>& vertices)
	: Collider(pParent, vertices, true)
{
	assert(vertices.size() == 4 && "Ladder collider does not have 4 vertices.");
}

bool LadderCollider::IsPlayerAtBottom() const
{
	const PhysicsHandler* physics{ m_pParent->GetScene()->GetPhysicsHandler() };
	return physics->Linecast(
		m_TransformedVertices[0] + Vector2f(0, 1),
		m_TransformedVertices[3] + Vector2f(0, 1),
		"Player",
		true
	).first;
}

bool LadderCollider::IsPlayerAtTop() const
{
	const PhysicsHandler* physics{ m_pParent->GetScene()->GetPhysicsHandler() };
	return physics->Linecast(
		m_TransformedVertices[1] - Vector2f(0, 1),
		m_TransformedVertices[2] - Vector2f(0, 1),
		"Player",
		true
	).first;
}

float LadderCollider::GetLadderX() const
{
	return m_pTransform->GetPosition().x;
}
