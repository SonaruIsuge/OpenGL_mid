

#include "Boss.h"


Boss::Boss(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player) : Enemy(shape, mxModelView, mxProjection, player)
{
	hasInit = false;
	// set enemy data
	type = Enum::OwnerType::Enemy;
	_moveSpeed = 4;
	_reloadTime = 1.2f;
	_fireCountdown = 0;
	_bulletSpeed = 8;
	_health = 3000;
	_damage = 20;
	_currentHealth = _health;
	state = nullptr;
	setActive(false);
}


Boss::~Boss() {}


void Boss::update(float dt) 
{
	if (!active) return;

	if(state != nullptr) state->stateStay(dt);
	
	_clock += dt;

	//movement(dt);
	shape->update(dt);
	//fire(dt);
	collider->updateCollider(shape->getWorldPosition());

	// set hit effect
	if (_bHit) {
		_hitTime = _clock;
		this->shape->setColor(vec4(1, 0, 0, 1));
		_bHit = false;
	}
	if (_clock - _hitTime >= 0.05f) {
		this->shape->setColor(selfColor);
		_clock = 0;
	}

	
	if (_currentHealth <= 0)
	{
		setActive(false);
	}
}


void Boss::init(vec3 initPos, vec3 initRot, float initScale)
{
	if (hasInit) return;

	this->setActive(true);
	this->shape->position = initPos;
	this->shape->rotation = initRot;
	this->shape->scale = vec3(initScale, initScale, initScale);
	_currentHealth = _health;

	changeState(new BossNormalState(this));
	hasInit = true;
}


void Boss::movement(float dt)
{
	//if (state != nullptr) this->state->move(dt);
}


void Boss::fire(float dt)
{
	//if (state != nullptr) this->state->fire(dt);
}


void Boss::changeState(State* newState) 
{
	if (state != nullptr) this->state->stateExit();
	this->state = newState;
	if (state != nullptr) this->state->stateEnter();
}