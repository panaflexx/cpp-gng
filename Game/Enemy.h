#pragma once
class Enemy
{
public:
	explicit Enemy();
	virtual ~Enemy() = default;

	void Damage();
	virtual void OnDeath() = 0;
private:
	int m_Health{};
};

