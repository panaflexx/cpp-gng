#pragma once
#include "Component.h"
#include "Vector2f.h"

class Transform final : public Component
{
public:
	explicit Transform(Entity* parent);
	explicit Transform(Entity* parent, Vector2f startingPos);

	Vector2f GetPosition() const;

	void SetPosition(Vector2f newPos);
	void MovePosition(Vector2f delta);

	float GetScale() const;
	void SetScale(float newScale);

private:
	Vector2f m_Position;
	float m_Scale;
};
