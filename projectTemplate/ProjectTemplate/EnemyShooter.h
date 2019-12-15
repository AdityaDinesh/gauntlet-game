#pragma once
#include "Component.h"

class EnemyShooter : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(EnemyShooter, Component)

public:
	std::string prefabGUID;
	float moveSpeed = 50;
	float time = 0;
	sf::Vector2f mousePos;

protected:
	void initialize() override;

public:
	EnemyShooter() = default;
	~EnemyShooter();
	void update(float deltaTime) override;
	void load(json::JSON& node) override;
	void onTriggerEnter(const Collision* const collisionData) override;
	void setEnabled(bool _enabled) override;
};


