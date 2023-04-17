#pragma once
#include "Collider.h"

class Renderer;

class Projectile final : public Collider
{
public:
	enum class Type
	{
		player, enemy
	};
	struct FireData
	{
		Type type;
		Vector2f start;
		Vector2f velocity;
		int spriteIndex;
		float width;
		float height;
	};
	
	explicit Projectile(Entity* pParent);
	void Initialize() override;

	void Update(float deltaTime) override;

	void SetFireData(const FireData& data);

	void OnCollisionEnter(Collider* other, float deltaTime, Vector2f normal) override;

private:
	Renderer* m_pRenderer{ nullptr };

	Type m_Type;
	Vector2f m_Velocity{};

	const float m_MaxLifetime{ 3.f };
	float m_Lifetime{};
};
