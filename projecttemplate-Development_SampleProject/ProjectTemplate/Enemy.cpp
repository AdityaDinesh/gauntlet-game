#include "GameCore.h"
#include "Enemy.h"
#include "Player.h"
#include "ProjectEngine.h"
#include "ICollidable.h"

IMPLEMENT_DYNAMIC_CLASS(Enemy)

void Enemy::initialize()
{
	if (!isEnabled())
	{
		return;
	}
	Component::initialize();
	ProjectEngine::instance().setEnemy(this);
}

Enemy::~Enemy()
{
	ProjectEngine::instance().setEnemy(nullptr);
}

void Enemy::update(float deltaTime)
{
	if (!getGameObject()->isEnabled() || !enabled)
	{
		return;
	}
	if (win)
	{
		return;
	}
	sf::Vector2f moveOffset(0, 0);
	sf::Vector2f playerPos(0, 0);
	sf::Vector2f enemyPos = getGameObject()->getTransform()->getPosition();

	std::string player = "Player";
	GameObject* playerObj = GameObjectManager::instance().getGameObjectWithComponent(player);
	playerPos = playerObj->getTransform()->getPosition();

	if (playerPos.y > enemyPos.y)
	{
		moveOffset.y += moveSpeed * deltaTime;
	}

	if (playerPos.y < enemyPos.y)
	{
		moveOffset.y -= moveSpeed * deltaTime;
	}

	if (playerPos.x < enemyPos.x)
	{
		moveOffset.x -= moveSpeed * deltaTime;
	}

	if (playerPos.x > enemyPos.x)
	{
		moveOffset.x += moveSpeed * deltaTime;
	}

	getGameObject()->getTransform()->translate(moveOffset);
}

void Enemy::load(json::JSON& node)
{
	Component::load(node);
	if (node.hasKey("moveSpeed"))
	{
		moveSpeed = node["moveSpeed"].ToFloat();
	}
}

void Enemy::setEnabled(bool _enabled)
{
	enabled = _enabled;
	if (enabled && getGameObject()->isEnabled() && !initialized)
	{
		initialize();
	}
}


void Enemy::onTriggerEnter(const Collision* const collisionData)
{
	int otherColliderIx = 1;
	if (collisionData->colliders[otherColliderIx]->getGameObject() == getGameObject())
	{
		otherColliderIx = 0;
	}

	collisionData->colliders[otherColliderIx]->getGameObject()->getComponent("Text")->setEnabled(true);
	win = true;
}
