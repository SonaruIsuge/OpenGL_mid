#pragma once


#include "Enemy.h"
#include "BossNormalState.h"
#include "BossAdvanceState.h"


class Boss : public Enemy
{
private:
	
	State* state;

	bool hasInit;

public:

	Boss(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player);
	~Boss();

	void init(vec3 initPos, vec3 initRot, float initScale) override;
	void update(float dt) override;
	void movement(float dt) override;
	void fire(float dt) override;
	void changeState(State* newState);
};