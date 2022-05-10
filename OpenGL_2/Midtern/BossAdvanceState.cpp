

#include "BossNormalState.h"
#include "BossAdvanceState.h"
#include "BossFinalState.h"
#include "BossAShape.h"
#include "BulletManager.h"
#include "EnemyController.h"


BossAdvanceState::BossAdvanceState(Character* owner) : State(owner)
{

}


BossAdvanceState::~BossAdvanceState() {}


void BossAdvanceState::stateEnter()
{
	this->owner->changeShape(this->owner->shape, new BossAShape);

	reloadTime = 0.04f;
	reloadTimer = 0;

	bulletSpeed = 4;
	moveSpeed = 0;

	rotateTime = 1;
	rotateTimer = 0;

	moveTime = 5;
	moveTimer = 0;

	longReloadTime = 0.2;
	longReloadTimer = 0;

	bulletNum = 120;
	bulletCount = 0;

	this->owner->shape->position = vec3(0, 0, 0);
	this->owner->shape->rotation = vec3(0, 0, 0);
	this->owner->shape->setColor(BOSS_ADVANCE_COLOR);
}


void BossAdvanceState::stateStay(float dt)
{
	move(dt);
	fire(dt);

	// set state
	if (owner->getHealthPercent() <= 0.4f) {
		((Boss*)owner)->changeState(new BossFinalState(owner));
	}
	
}


void BossAdvanceState::stateExit()
{
	this->owner->shape->position = vec3(0, VP_HALFWIDTH - 2, 0);
	this->owner->shape->rotation = vec3(0, 0, 0);
}


void BossAdvanceState::move(float dt)
{
	moveTimer += dt;
	rotateTimer += dt;
	if (moveTimer >= moveTime) {
		float randX = EnemyController::getInstance()->random->randFloat(-VP_HALFWIDTH * 0.6, VP_HALFWIDTH * 0.6);
		float randY = EnemyController::getInstance()->random->randFloat(-VP_HALFWIDTH * 0.3, VP_HALFWIDTH * 0.3);
		owner->shape->position = vec3(randX, randY, 0);

		moveTimer -= moveTime;
	}

		owner->shape->rotation.z = rotateTimer * (360 / rotateTime);

		if (rotateTimer >= rotateTime) rotateTimer -= rotateTime;
}


void BossAdvanceState::fire(float dt)
{
	reloadTimer += dt;
	longReloadTimer += dt;

	if (reloadTimer >= reloadTime && bulletCount < bulletNum && longReloadTimer <= moveTime - longReloadTime) {
		BulletManager::getInstance()->fire(Enum::BulletType::Boss,
			owner, owner->shape->position + EnemyController::getInstance()->random->randPointInRound(2), 
			normalize(owner->shape->position + EnemyController::getInstance()->random->randPointInRound(2) - owner->shape->position),
			vec3(0, 0, 180), 1, bulletSpeed * (1+ EnemyController::getInstance()->random->rand01()));
		bulletCount++;
		reloadTimer -= reloadTime;
	}

	if (longReloadTimer >= moveTime) {
		longReloadTimer -= moveTime;
		bulletCount = 0;
	}
}