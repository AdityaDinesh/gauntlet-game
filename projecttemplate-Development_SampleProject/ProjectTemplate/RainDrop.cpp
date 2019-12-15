#include "GameCore.h"
#include "Raindrop.h"

IMPLEMENT_DYNAMIC_CLASS(RainDrop)

void RainDrop::initialize()
{
    texturePath = "../Assets/Raindrop.png";

    Sprite::initialize();

    // Should be loaded from a file
    minSpeed = sf::Vector2f(0.0f, 20.0f);
    maxSpeed = sf::Vector2f(0.0f, 100.0f);

    speed.x = ((maxSpeed.x - minSpeed.x) * (float)Random.Random()) + minSpeed.x;
    speed.y = ((maxSpeed.y - minSpeed.y) * (float)Random.Random()) + minSpeed.y;

    sf::Vector2f pos;
    pos.x = RenderSystem::instance().getRenderWindow()->getSize().x * (float)Random.Random();
    pos.y = -64.0f;
    gameObject->setPosition(pos);
}

void RainDrop::update(float deltaTime)
{
    Component::update(deltaTime);

    if (gameObject->getPosition().y < RenderSystem::instance().getRenderWindow()->getSize().y + 64.0f)
    {
        gameObject->getPosition().y += speed.y * deltaTime;
    }
    else
    {
        GameObjectManager::instance().removeGameObject(gameObject);
    }
}
