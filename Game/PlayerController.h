#pragma once
#include "Component.h"

class PlayerController final : public Component
{
public:
	explicit PlayerController(Entity* parent)
		: Component(parent)
	{
	}

	void Initialize() override;
	void Update(float deltaTime) override;
	void Draw() const override;
};
