#pragma once

#include "State.h"

class BossFinalState : public State
{
private:
	vec3 randMoveDir;
	vec3 randMoveDes;

	vec3 subFirePos;
	float subFireMoveSpeed;
	float subFireBulletSpeed;
	float subFireTimer;
	float subFireTime;

public:

	BossFinalState(Character* owner);
	~BossFinalState();

	void stateEnter();
	void stateStay(float dt);
	void stateExit();

	void move(float dt);
	void fire(float dt);
};