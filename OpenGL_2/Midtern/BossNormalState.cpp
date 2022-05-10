

#include "BossNormalState.h"
#include "BulletManager.h"


BossNormalState::BossNormalState(Character* owner) : State(owner)
{
	
}


BossNormalState::~BossNormalState(){}


void BossNormalState::stateEnter() 
{
	reloadTime = 0.08f;
	reloadTimer = 0;

	bulletSpeed = 4;
	moveSpeed = 6;

	rotateTime = 3;
	rotateTimer = 0;
	moveTime = 0;
	moveTimer = 0;

	points[0] = owner->shape->position + vec3(0, 0 - owner->shape->boundsRadius, 0);
	points[1] = owner->shape->position + vec3(0 - owner->shape->boundsRadius, 0, 0);
	points[2] = owner->shape->position + vec3(0, 0 + owner->shape->boundsRadius, 0);
	points[3] = owner->shape->position + vec3(0 + owner->shape->boundsRadius, 0, 0);
}


void BossNormalState::stateStay(float dt) 
{
	move(dt);
	fire(dt);

	// set state 
	if (owner->getHealthPercent() <=  0.75f) {
		 ((Boss*)owner)->changeState(new BossAdvanceState(owner));
	}
}


void BossNormalState::stateExit() 
{
	this->owner->shape->position = vec3(0, VP_HALFWIDTH - 2, 0);
	this->owner->shape->rotation = vec3(0, 0, 0);
}


void BossNormalState::move(float dt) 
{
	
	rotateTimer += dt;

	owner->shape->rotation.z = rotateTimer * (360 / rotateTime);
	
	if (rotateTimer >= rotateTime) rotateTimer -= rotateTime;
}


void BossNormalState::fire(float dt) 
{
	reloadTimer += dt;

	if (reloadTimer >= reloadTime) {
		for (int i = 0; i < 4; i++) {
			BulletManager::getInstance()->fire(Enum::BulletType::Boss,
				owner, calShootPoint(points[i]), normalize(calShootPoint(points[i]) - owner->shape->position), vec3(0, 0, 180), 0.8f, bulletSpeed);
		}

		reloadTimer -= reloadTime;
	}
}


vec3 BossNormalState::calShootPoint(vec3 shootPoint) {
	float rotateAngle = owner->shape->rotation.z;
	
	vec3 result;
	result.x = (shootPoint.x - owner->shape->position.x) * cosf(rotateAngle * PI / 180) - (shootPoint.y - owner->shape->position.y) * sinf(rotateAngle * PI / 180) + owner->shape->position.x;
	result.y = (shootPoint.x - owner->shape->position.x) * sinf(rotateAngle * PI / 180) + (shootPoint.y - owner->shape->position.y) * cosf(rotateAngle * PI / 180) + owner->shape->position.y;
	result.z = 0;

	return result;
}