

#include "BossFinalState.h"
#include "BossAdvanceState.h"
#include "BossAShape.h"
#include "BossFShape.h"
#include "BulletManager.h"
#include "EnemyController.h"


BossFinalState::BossFinalState(Character* owner) : State(owner)
{

}


BossFinalState::~BossFinalState() {}


void BossFinalState::stateEnter()
{
	this->owner->changeShape(this->owner->shape, new BossFShape);

	reloadTime = 1.5f;
	reloadTimer = 0;

	bulletSpeed = 6;
	moveSpeed = 3;

	rotateTime = 1;
	rotateTimer = 0;

	moveTime = 1.5;
	moveTimer = 0;

	randMoveDir = vec3(0, 0, 0);
	randMoveDes = vec3(0, 0, 0);

	subFirePos = vec3(VP_HALFWIDTH, VP_HALFWIDTH, 0);
	subFireMoveSpeed = 9;
	subFireBulletSpeed = 6;
	subFireTimer = 0;
	subFireTime = 0.4f;

	this->owner->shape->position = vec3(0, VP_HALFWIDTH * 0.5, 0);
	this->owner->shape->rotation = vec3(0, 0, 0);
	this->owner->shape->setColor(BOSS_FINAL_COLOR);
}


void BossFinalState::stateStay(float dt)
{
	move(dt);
	fire(dt);

	// set state
	if (owner->getHealthPercent() <= 0) {
		((Boss*)owner)->setActive(false);
	}

}


void BossFinalState::stateExit()
{
	this->owner->shape->position = vec3(0, 0, 0);
	this->owner->shape->rotation = vec3(0, 0, 0);
}


void BossFinalState::move(float dt)
{
	moveTimer += dt;
	if (moveTimer >= moveTime) {
		randMoveDes = vec3(EnemyController::getInstance()->random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), 
			EnemyController::getInstance()->random->randFloat(VP_HALFWIDTH * 0.9, VP_HALFWIDTH * 0.7), 0);
		randMoveDir = normalize(randMoveDes - this->owner->shape->position);
		moveTimer -= moveTime;
		//printf("Des(%f, %f) Dir(%f, %f)\n", randMoveDes.x, randMoveDes.y, randMoveDir.x, randMoveDir.y);
	}
	else if(length(this->owner->shape->position - randMoveDes) > 0.05f) {
		this->owner->shape->position += randMoveDir * moveSpeed * dt;
	}
}


void BossFinalState::fire(float dt)
{
	// main fire
	
	reloadTimer += dt;

	if (reloadTimer >= reloadTime) {
		for (int i = 0; i < 24; i++) {
			vec3 pos = vec3(0.2f * cos(15.0 * i * PI / 180), 0.2f * sin(15.0 * i * PI / 180), 0);
			BulletManager::getInstance()->fire(Enum::BulletType::Boss, owner, 
				this->owner->shape->position + pos,
				normalize( (pos) / cosf(45 * PI / 180)),
				vec3(0, 0, 15.0f * i), 0.8f, bulletSpeed);
			BulletManager::getInstance()->fire(Enum::BulletType::Boss, owner,
				this->owner->shape->position + pos,
				normalize((pos) / cosf(0 * PI / 180)),
				vec3(0, 0, 15.0f * i), 0.8f, bulletSpeed * 0.8);
			BulletManager::getInstance()->fire(Enum::BulletType::Boss, owner,
				this->owner->shape->position + pos,
				normalize((pos) / cosf(-45 * PI / 180)),
				vec3(0, 0, 15.0f * i), 0.8f, bulletSpeed * 0.6);
		}

		reloadTimer -= reloadTime;
	}


	// sub fire
	if (subFirePos.x >= VP_HALFWIDTH && subFirePos.y >= -VP_HALFWIDTH) subFirePos.y -= subFireMoveSpeed * dt;
	else if (subFirePos.x >= -VP_HALFWIDTH && subFirePos.y <= -VP_HALFWIDTH) subFirePos.x -= subFireMoveSpeed * dt;
	else if (subFirePos.x <= -VP_HALFWIDTH && subFirePos.y <= VP_HALFWIDTH) subFirePos.y += subFireMoveSpeed * dt;
	else subFirePos.x += subFireMoveSpeed * dt;

	subFireTimer += dt;
	if (subFireTimer >= subFireTime) {
		BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy,
			owner, subFirePos,
			normalize(vec3(-subFirePos.x, -subFirePos.y, 0)),
			vec3(0, 0, 0), 0.8, subFireBulletSpeed);
		BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy,
			owner, -subFirePos,
			normalize(vec3(subFirePos.x, subFirePos.y, 0)),
			vec3(0, 0, 0), 0.8, subFireBulletSpeed);
		BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy,
			owner, vec3(-subFirePos.x, subFirePos.y, 0),
			normalize(vec3(subFirePos.x, -subFirePos.y, 0)),
			vec3(0, 0, 0), 0.8, subFireBulletSpeed);
		BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy,
			owner, vec3(subFirePos.x, -subFirePos.y, 0),
			normalize(vec3(-subFirePos.x, subFirePos.y, 0)),
			vec3(0, 0, 0), 0.8, subFireBulletSpeed);
		subFireTimer -= subFireTime;
	}
	//printf("(%f, %f)\n", subFirePos.x, subFirePos.y);
}