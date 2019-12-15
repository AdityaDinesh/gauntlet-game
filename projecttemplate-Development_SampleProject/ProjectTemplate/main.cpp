#include "GameCore.h"
#include "GameEngine.h"
#include "ProjectEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "SpawnFactory.h"

void registerGameClasses()
{
	REGISTER_DYNAMIC_CLASS(Player);
	REGISTER_DYNAMIC_CLASS(Enemy);
	REGISTER_DYNAMIC_CLASS(SpawnFactory);
}

int main(int argc, char* argv[])
{
    registerGameClasses();

    GameEngine::instance().initialize(&ProjectEngine::instance());
	GameEngine::instance().gameLoop();

	return -1;
}