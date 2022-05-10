#pragma once

#include "State.h"

class BossNormalState : public State
{
private:
	vec3 calShootPoint(vec3 shootPoint);
	
	vec3 points[4];

public:

	BossNormalState(Character* owner);
	~BossNormalState();

	void stateEnter();
	void stateStay(float dt);
	void stateExit();

	void move(float dt);
	void fire(float dt);
};