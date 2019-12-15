#pragma once
#include "Component.h"

class SpawnFactory : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(SpawnFactory, Component)

public:
	float moveSpeed = 50;
	float time = 0;
	sf::Vector2f mousePos;

protected:
	void initialize() override;

public:
	SpawnFactory() = default;
	~SpawnFactory();
	void update(float deltaTime) override;
	void load(json::JSON& node) override;
	void setEnabled(bool _enabled) override;
};


