#pragma once

#include "../Header/Angel.h"
#include "Shape.h"
#include "Collider.h"
#include "Enum.h"

class Character 
{
protected:
	float _clock;

	Enum::OwnerType type;
	int _health;
	int _damage;

	int _currentHealth;

	bool _bHit;

public:

	Shape* shape;
	Collider* collider;

	Character();
	virtual ~Character();

	void changeShape(Shape* oldShpae, Shape* newShape);
	void resetTransform();

	virtual void update(float dt) = 0;
	virtual void init(vec3 initPos, vec3 initRot, float initScale) = 0;
	virtual void movement(float dt) = 0;
	virtual void fire(float dt) = 0;
	virtual void takeDamage(int damage) = 0;

	Enum::OwnerType getType();
	int getHealth();
	float getHealthPercent();
	int getDamage();
};