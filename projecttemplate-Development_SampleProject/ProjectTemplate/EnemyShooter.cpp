#include "GameCore.h"
#include "EnemyShooter.h"
#include "PrefabAsset.h"
#include "ProjectEngine.h"
#include "ICollidable.h"

IMPLEMENT_DYNAMIC_CLASS(EnemyShooter)

void EnemyShooter::initialize()
{
	if (!isEnabled())
	{
		return;
	}
	Component::initialize();
	ProjectEngine::instance().setEnemyShooter(this);
}

EnemyShooter::~EnemyShooter()
{
	ProjectEngine::instance().setEnemyShooter(nullptr);
}

void EnemyShooter::update(float deltaTime)	
{
	if (!getGameObject()->isEnabled() || !enabled)
	{
		return;
	}

	time += deltaTime;
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

	if (time > 4)
	{
		PrefabAsset* prefabTest = (PrefabAsset*)AssetManager::instance().GetAssetByGUID("804f8df5-aa93-4209-950c-c39b3f2f1ece");
		GameObject* enemy = GameObjectManager::instance().instantiatePrefab(prefabTest->getID());
		enemy->getTransform()->setPosition(getGameObject()->getTransform()->getPosition());
		time = 0;
	}
	getGameObject()->getTransform()->translate(moveOffset);
	
}

void EnemyShooter::load(json::JSON& node)
{
	Component::load(node);
	if (node.hasKey("moveSpeed"))
	{
		moveSpeed = node["moveSpeed"].ToFloat();
	}
}

void EnemyShooter::setEnabled(bool _enabled)
{
	enabled = _enabled;
	if (enabled && getGameObject()->isEnabled() && !initialized)
	{
		initialize();
	}
}


void EnemyShooter::onTriggerEnter(const Collision* const collisionData)
{
	int otherColliderIx = 1;
	if (collisionData->colliders[otherColliderIx]->getGameObject() == getGameObject())
	{
		otherColliderIx = 0;
	}
}
