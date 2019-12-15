#include "GameCore.h"
#include "Player.h"
#include "PrefabAsset.h"
#include "ProjectEngine.h"
#include "ICollidable.h"

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::initialize()
{
	if (!isEnabled())
	{
		return;
	}
	Component::initialize();
	ProjectEngine::instance().setPlayer(this);
}

Player::~Player()
{
	ProjectEngine::instance().setPlayer(nullptr);
}

void Player::update(float deltaTime)
{
	if (!getGameObject()->isEnabled() || !enabled)
	{
		return;
	}
	if (win)
	{
		return;
	}

	if (InputManager::instance().getKeyState(sf::Keyboard::Tilde) == InputManager::PushState::Up)
	{
		ProjectEngine::instance().pauseMenu();
	}

	sf::Vector2f moveOffset(0, 0);

	if (InputManager::instance().getKeyState(sf::Keyboard::Down) == InputManager::PushState::Held)
	{
		moveOffset.y += moveSpeed * deltaTime;
		
	}
	if (InputManager::instance().getKeyState(sf::Keyboard::Up) == InputManager::PushState::Held)
	{
		moveOffset.y -= moveSpeed * deltaTime;
		
	}
	if (InputManager::instance().getKeyState(sf::Keyboard::Left) == InputManager::PushState::Held)
	{
		moveOffset.x -= moveSpeed * deltaTime;
		
	}
	if (InputManager::instance().getKeyState(sf::Keyboard::Right) == InputManager::PushState::Held)
	{
		moveOffset.x += moveSpeed * deltaTime;
		
	}
	if (InputManager::instance().getMouseButtonState(sf::Mouse::Button::Left) == InputManager::PushState::Down)
	{
		mousePos = InputManager::instance().getMousePosition();
		PrefabAsset* prefabTest = (PrefabAsset*)AssetManager::instance().GetAssetByGUID("04127430-547d-4db3-936b-666e63665eae");
		GameObject* go = GameObjectManager::instance().instantiatePrefab(prefabTest->getID());
	}
	
	getGameObject()->getTransform()->translate(moveOffset);
}

void Player::load(json::JSON& node)
{
	Component::load(node);
	if (node.hasKey("moveSpeed"))
	{
		moveSpeed = node["moveSpeed"].ToFloat();
	}
}

void Player::setEnabled(bool _enabled)
{
	enabled = _enabled;
	if (enabled && getGameObject()->isEnabled() && !initialized)
	{
		initialize();
	}
}


void Player::onTriggerEnter(const Collision* const collisionData)
{
	int otherColliderIx = 1;
	if (collisionData->colliders[otherColliderIx]->getGameObject() == getGameObject())
	{
		otherColliderIx = 0;
	}

	collisionData->colliders[otherColliderIx]->getGameObject()->getComponent("Text")->setEnabled(true);


	std::string lvl2 = "../Assets/Levels/level2.json";
	std::string lvl1 = "../Assets/Levels/level1.json";

	FileSystem::instance().load(lvl2, true);
	FileSystem::instance().unload(lvl1);
	RenderSystem::instance().renderText(0.0, true);
	win = true;
}
