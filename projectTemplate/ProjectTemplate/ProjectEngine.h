///-------------------------------------------------------------------------------------------------
// file: ProjectEngine.h
//
// author: William Barry
// date: 10/28/2019
//
// summary:	The Project Engine
///-------------------------------------------------------------------------------------------------
#ifndef _PROJECTENGINE_H_
#define _PROJECTENGINE_H_
#pragma once

#include "ISystem.h"
class Player;
class Enemy;
class Projectile;
class SpawnFactory;
class ShootEnemy;
class EnemyShooter;
class ProjectEngine final : public ISystem
{
	Player* playerScript = nullptr;
	Enemy* enemyScript = nullptr;
	Projectile* projectileScript = nullptr;
	SpawnFactory* spawnFactory = nullptr;
	ShootEnemy* shootEnemy = nullptr;
	EnemyShooter* enemyShooter = nullptr;


	std::string levelFile = "../Assets/Levels/level1.json";
	std::string levelFile2 = "../Assets/Levels/level2.json";

	bool loaded = false;
	sf::RenderWindow mainMenuWindow;
	sf::RenderWindow pauseWindow;

public:
    void initialize() override;
    void update(float deltaTime)override;
	void setPlayer(Player* _player) { playerScript = _player; }
	void mainMenu();
	void pauseMenu();
	void closePauseMenu();
	void closeMainMenu();

	void setEnemy(Enemy* _enemy) { enemyScript = _enemy; }
	void setProjectile(Projectile* _projectile) { projectileScript = _projectile; }
	void setSpawnFactory(SpawnFactory* _spawnFactory) { spawnFactory = _spawnFactory; }
	void setShootEnemy(ShootEnemy* _shootEnemy) { shootEnemy = _shootEnemy; }
	void setEnemyShooter(EnemyShooter* _enemyShooter) { enemyShooter = _enemyShooter; }



    DECLARE_SINGLETON(ProjectEngine)
};

#endif