#include "GameCore.h"
#include "ProjectEngine.h"
#include "Player.h"

void ProjectEngine::initialize()
{
	FileSystem::instance().load(levelFile, true);
	loaded = true;
}

void ProjectEngine::update(float deltaTime)
{
	if (!loaded)
	{
		return;
	}
	if (playerScript == nullptr)
	{
		return;
	}
	if (!playerScript->win)
	{
		return;
	}
	if (InputManager::instance().getMouseButtonState(sf::Mouse::Button::Left) == InputManager::PushState::Held)
	{
		loaded = false;
		FileSystem::instance().unload(levelFile);
	}
}
