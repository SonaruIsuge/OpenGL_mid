#pragma once

#include "Character.h"
//#include "Shape.h"

class State 
{
protected:
	Character* owner;

	float reloadTime;
	float reloadTimer;

	float bulletSpeed;
	float moveSpeed;
	float moveTime;
	float moveTimer;
	float rotateTime;
	float rotateTimer;

public:

	State(Character* owner);
	~State();

	virtual void stateEnter() = 0;
	virtual void stateStay(float dt) = 0;
	virtual void stateExit() = 0;

	virtual void move(float dt) = 0;
	virtual void fire(float dt) = 0;
};