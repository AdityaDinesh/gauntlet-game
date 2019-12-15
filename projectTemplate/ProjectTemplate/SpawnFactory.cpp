#include "GameCore.h"
#include "SpawnFactory.h"
#include "PrefabAsset.h"
#include "ProjectEngine.h"
#include "ICollidable.h"

IMPLEMENT_DYNAMIC_CLASS(SpawnFactory)

void SpawnFactory::initialize()
{
	if (!isEnabled())
	{
		return;
	}
	Component::initialize();
	ProjectEngine::instance().setSpawnFactory(this);
}

SpawnFactory::~SpawnFactory()
{
	ProjectEngine::instance().setSpawnFactory(nullptr);
}

void SpawnFactory::update(float deltaTime)
{
	if (!getGameObject()->isEnabled() || !enabled)
	{
		return;
	}

	time += deltaTime;

	if (time > 2)
	{
		PrefabAsset* prefabTest = (PrefabAsset*)AssetManager::instance().GetAssetByGUID(prefabGUID);
		GameObject* enemy = GameObjectManager::instance().instantiatePrefab(prefabTest->getID());
		enemy->getTransform()->setPosition(getGameObject()->getTransform()->getPosition());
		time = 0;
	}

}

void SpawnFactory::load(json::JSON& node)
{
	Component::load(node);
	if (node.hasKey("moveSpeed"))
	{
		moveSpeed = node["moveSpeed"].ToFloat();
	}
	if (node.hasKey("prefabGUID"))
	{
		prefabGUID = node["prefabGUID"].ToString();
	}
}

void SpawnFactory::setEnabled(bool _enabled)
{
	enabled = _enabled;
	if (enabled && getGameObject()->isEnabled() && !initialized)
	{
		initialize();
	}
}