#pragma once
#include "Component.h"

class Projectile : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Projectile, Component)

public:
	float moveSpeed = 1000;
	bool win = false;
	sf::Vector2f mousePos;
	sf::Vector2f playerPos;
	sf::Vector2f direction;

protected:
	void initialize() override;

private:
	GameObject* playerObj = nullptr;

public:
	Projectile() = default;
	~Projectile();
	void update(float deltaTime) override;
	void load(json::JSON& node) override;
	void onTriggerEnter(const Collision* const collisionData) override;
	void onCollisionEnter(const Collision* const collisionData) override;
	void setEnabled(bool _enabled) override;
	void setTarget();
};

