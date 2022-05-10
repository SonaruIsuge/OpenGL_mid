#pragma once

#include "ObjectPool.h"
#include "Enemy.h"
#include "CurveEnemy.h"
#include "BigEnemy.h"
#include "Boss.h"
#include "Character.h"
#include "Random.h"


class EnemyController 
{
private:
	
	static EnemyController* _instance;

	float _clock;
	float _enemyInitCooldown;
	float _cooldownTimer;

	int _currentWave;
	int _maxEnemyNum;

	int killedBigEnemy;
	bool _isBossAppear;

	void SetWave1Perform(float dt, float initCooldown, int maxEnemy);
	void SetWave2Perform(float dt, float initCooldown, int maxEnemy);
	void SetWave3Perform(float dt, float initCooldown, int maxEnemy);
	void setBossFight(float dt);
	
public:

	Random* random;

	int deadEnemy;
	int enemyInField;

	Character* player;
	ObjectPool<Enemy> enemies;
	ObjectPool<Enemy> curveEnemies;
	ObjectPool<Enemy> bigEnemies;
	Boss* boss;

	static EnemyController* getInstance();

	EnemyController();
	~EnemyController();
	void destroy();

	void updateEnemyPerform(float dt);
	void ColliderControl(Enemy* enemy);

	void init(Character* player, mat4 mxModelView, mat4 mxProjection);
	void draw();
	void update(float dt);
};
