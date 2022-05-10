#pragma once

#include "State.h"

class BossAdvanceState : public State
{
private:

	float longReloadTime;
	float longReloadTimer;
	int bulletNum;
	int bulletCount;

public:

	BossAdvanceState(Character* owner);
	~BossAdvanceState();

	void stateEnter();
	void stateStay(float dt);
	void stateExit();

	void move(float dt);
	void fire(float dt);
};