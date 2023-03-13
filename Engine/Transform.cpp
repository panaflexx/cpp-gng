#include "base.h"
#include "Transform.h"

Transform::Transform(Entity* parent)
	: Component(parent)
	, m_Position{ Vector2f(0, 0) }
	, m_Scale{ 1.f }
{
}

Transform::Transform(Entity* parent, Vector2f startingPos)
	: Component(parent)
	, m_Position{ startingPos }
	, m_Scale{ 1.f }
{
}

Vector2f Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(Vector2f newPos)
{
	m_Position = newPos;
}

void Transform::MovePosition(Vector2f delta)
{
	m_Position += delta;
}

float Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float newScale)
{
	m_Scale = newScale;
}
