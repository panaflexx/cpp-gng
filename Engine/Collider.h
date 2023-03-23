#pragma once
#include "Component.h"
#include <vector>
#include "Vector2f.h"

class Transform;

class Collider : public Component
{
public:
	explicit Collider(Entity* pParent, std::vector<Vector2f> vertices);
	~Collider() override;

	void Initialize() override;

	virtual void OnCollisionUpdate(Collider* other, float deltaTime);
	virtual void OnCollisionEnter(Collider* other, float deltaTime);
	virtual void OnCollisionExit(Collider* other, float deltaTime);

	void DrawDebugCollider() const;

	void RecalculateTransformedVertices();

	bool IsTrigger() const;
	void SetTrigger(bool newVal);

	bool CompareTag(const std::string& tag) const;

	std::vector<Vector2f>& GetBaseVertices();
	void SetBaseVertices(std::vector<Vector2f> newVertices);
	const std::vector<Vector2f>& GetTransformedVertices();

private:
	Transform* m_pTransform{ nullptr };

	// Whether the collider is pass-through
	bool m_IsTrigger{ false };

	// Non-transformed vertices in relation to the transforms position
	std::vector<Vector2f> m_BaseVertices;
	// Computed (cached) transformed vertices
	std::vector<Vector2f> m_TransformedVertices;
};