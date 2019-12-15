#pragma once
#include "Component.h"

class Player : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

public:
	float moveSpeed = 50;
	bool win = false;
	sf::Vector2f mousePos;

protected:
	void initialize() override;

public:
	Player() = default;
	~Player();
	void update(float deltaTime) override;
	void load(json::JSON& node) override;
	void onTriggerEnter(const Collision* const collisionData) override;
	void setEnabled(bool _enabled) override;
};

