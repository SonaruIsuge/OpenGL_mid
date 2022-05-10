#pragma once


#include "../Header/Angel.h"
#include "Character.h"

class Enemy : public Character 
{
protected:
	float _moveSpeed;
	float _reloadTime;
	float _fireCountdown;
	float _bulletSpeed;
	float _hitTime;
	float _moveClock;

	bool _bReload;
	bool active;

	Shape* player;
	vec4 selfColor;

public:

	Enemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player);
	~Enemy() {};

	void setActive(bool active);
	bool isActive();
	void init(vec3 initPos, vec3 initRot, float initScale);

	void update(float dt);
	void movement(float dt);
	void fire(float dt);
	void takeDamage(int damage);

	void setSelfColor(vec4 color);
};