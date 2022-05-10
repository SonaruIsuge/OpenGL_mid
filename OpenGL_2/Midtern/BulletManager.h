#pragma once

#include "../Header/Angel.h"
//#include "ObjectPool.h"
#include "Bullet.h"
#include "EnemyController.h"
#include "Random.h"
 
#define PLAYER_BULLET_COLOR vec4(0.3, 0.93, 0.58, 1.0)
#define ENEMY_BULLET_COLOR vec4(1.0, 0.27, 0.0, 1.0)
#define BOSS_BULLET_COLOR vec4(0.545, 0.0, 0.545, 1.0)
#define BOSS_ADVANCE_COLOR vec4(0.49, 0.15, 0.80, 1.0)
#define BOSS_FINAL_COLOR vec4(0.545, 0.0, 0.0, 1.0)

class BulletManager
{
private:

	Random* random;
	static BulletManager* _instance;
	ObjectPool<Bullet> bulletPool;
	ObjectPool<Bullet> enemyBulletPool;
	ObjectPool<Bullet> bossBulletPool;

	Character* player;

	float _recycleTimer;

public:
	

	static BulletManager* getInstance();

	BulletManager();
	~BulletManager();
	void destroy();

	void init(Character* player, mat4 mxModelView, mat4 mxProjection, int size);
	void draw();
	void update(float dt);
	void fire(Enum::BulletType bulletType, Character* owner, vec3 origin, vec3 direction, vec3 rotation, float scale, float speed);
	void colliderUpdate(Node<Bullet>* node);
};