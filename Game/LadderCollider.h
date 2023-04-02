#pragma once
#include "Collider.h"

class LadderCollider final : public Collider
{
public:
	LadderCollider(Entity* pParent, const std::vector<Vector2f>& vertices);

	bool IsPlayerAtBottom() const;
	bool IsPlayerAtTop() const;

	float GetLadderX() const;
};

