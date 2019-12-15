#pragma once
#include "Component.h"

class Enemy : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Enemy, Component)

public:
	float moveSpeed = 50;
	bool win = false;
protected:
	void initialize() override;

public:
	Enemy() = default;
	~Enemy();
	void update(float deltaTime) override;
	void load(json::JSON& node) override;
	void onTriggerEnter(const Collision* const collisionData) override;
	void setEnabled(bool _enabled) override;
};

