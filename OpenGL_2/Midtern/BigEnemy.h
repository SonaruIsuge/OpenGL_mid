#pragma once


#include "Enemy.h"


class BigEnemy : public Enemy
{
private:

	int fireNumPerReload;
	int fireCount;

	float shortReloadTime;
	float _timer;
	float _moveXTimer;

	vec3 initPos;

public:
	bool reverse;

	BigEnemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player);
	~BigEnemy();

	void init(vec3 initPos, vec3 initRot, float initScale)override;
	void movement(float dt) override;
	void fire(float dt) override;
};