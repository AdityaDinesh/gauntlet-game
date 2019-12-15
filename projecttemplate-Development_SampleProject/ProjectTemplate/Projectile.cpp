#include "GameCore.h"
#include "Player.h"
#include "Projectile.h"
#include "ProjectEngine.h"
#include "ICollidable.h"


IMPLEMENT_DYNAMIC_CLASS(Projectile)

void Projectile::initialize()
{
	if (!isEnabled())
	{
		return;
	}
	Component::initialize();
	ProjectEngine::instance().setProjectile(this);

	setTarget();
}

Projectile::~Projectile()
{
	ProjectEngine::instance().setProjectile(nullptr);
	//playerObj = nullptr;
}

void Projectile::update(float deltaTime)
{
	if (!getGameObject()->isEnabled() || !enabled)
	{
		return;
	}
	if (win)
	{
		return;
	}
	getGameObject()->getTransform()->translate(direction * moveSpeed * deltaTime);
}

void Projectile::load(json::JSON& node)
{
	Component::load(node);
	if (node.hasKey("moveSpeed"))
	{
		moveSpeed = node["moveSpeed"].ToFloat();
	}
}

void Projectile::setEnabled(bool _enabled)
{
	enabled = _enabled;
	if (enabled && getGameObject()->isEnabled() && !initialized)
	{
		initialize();
	}
}

void Projectile::setTarget()
{
	std::string player = "Player";
	playerObj = GameObjectManager::instance().getGameObjectWithComponent(player);
	playerPos = playerObj->getTransform()->getPosition();
	Player* playerScript = (Player*)playerObj->getComponent("Player");
	mousePos = playerScript->mousePos;

	direction = mousePos - playerPos;

	getGameObject()->getTransform()->setPosition(playerPos);

	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));

	direction.x /= length;
	direction.y /= length;
}


void Projectile::onTriggerEnter(const Collision* const collisionData)
{
	int otherColliderIx = 1;
	if (collisionData->colliders[otherColliderIx]->getGameObject() == getGameObject())
	{
		otherColliderIx = 0;
	}

	collisionData->colliders[otherColliderIx]->getGameObject()->getComponent("Text")->setEnabled(true);
	win = true;
}

void Projectile::onCollisionEnter(const Collision* const collisionData)
{

	int otherColliderIx = 1;
	if (collisionData->colliders[otherColliderIx]->getGameObject() == getGameObject())
	{
		otherColliderIx = 0;
	}

	if (collisionData->colliders[otherColliderIx]->getGameObject() != playerObj)
	{
		GameObjectManager::instance().removeGameObject(collisionData->colliders[0]->getGameObject());
		GameObjectManager::instance().removeGameObject(collisionData->colliders[1]->getGameObject());
	}
}
