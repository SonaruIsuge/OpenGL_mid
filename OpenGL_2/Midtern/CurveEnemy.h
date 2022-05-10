#pragma once


#include "Enemy.h"


class CurveEnemy : public Enemy 
{
private:

	float _bulletRadFromBody;
	vec3 p0, p1, p2, p3;
	float _moveTimer;
	float _moveTime;

public:

	CurveEnemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player);
	~CurveEnemy();

	void init(vec3 initPos, vec3 initRot, float initScale) override;
	void movement(float dt) override;
	void fire(float dt) override;
};