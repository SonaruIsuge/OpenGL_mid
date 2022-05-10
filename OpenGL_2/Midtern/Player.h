#pragma once

#include "../header/Angel.h"
#include "Character.h"
#include "Random.h"
#include "Shield.h"

class Player : public Character
{
private:
	Random* random;
	float _reloadTime;
	float _fireCountdown;
	float _bulletSpeed;
	float _hitTime;

	bool _bEnableFire;
	bool _bReload;
	bool _bATField;

	int level;
	bool _canLevelUp;

public:
	Shield* shield;
	Player(Shape* shape, mat4 mxModelView, mat4 mxProjection);
	~Player() {};

	void init(vec3 initPos, vec3 initRot, float initScale);
	void draw();
	void update(float dt);
	void movement(float dt);
	void EnableFire(bool b);
	void fire(float dt);
	void takeDamage(int damage);
	void shieldControl();

	void levelManage();
	void firePower(float dt, int num);
};