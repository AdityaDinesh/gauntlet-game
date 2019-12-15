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
class EnemyShooter;
class ProjectEngine final : public ISystem
{
public:

	Player* playerScript = nullptr;
	Enemy* enemyScript = nullptr;
	Projectile* projectileScript = nullptr;
	SpawnFactory* spawnFactoryScript = nullptr;
	EnemyShooter* enemyShooterScript = nullptr;
	std::string levelFile = "../Assets/Levels/level1.json";
	bool loaded = false;
    void initialize() override;
    void update(float deltaTime)override;
	void setPlayer(Player* _player) { playerScript = _player; }
	void setEnemy(Enemy* _enemy) { enemyScript = _enemy; }
	void setProjectile(Projectile* _projectile) { projectileScript = _projectile; }
	void setSpawnFactory(SpawnFactory* _spawnfactory) { spawnFactoryScript = _spawnfactory; }
	void setEnemyShooter(EnemyShooter* _enemyShooter) { enemyShooterScript = _enemyShooter; }
    DECLARE_SINGLETON(ProjectEngine)
};

#endif