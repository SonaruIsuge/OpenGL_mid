

#include "Enemy.h"
#include "BulletManager.h"


Enemy::Enemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player)
{
	selfColor = vec4(0.73, 0.33, 0.83, 1);

	this->shape = shape;
	this->shape->init(selfColor, mxModelView, mxProjection);

	this->collider = new Collider(shape->getWorldPosition(), shape->boundsRadius, 1);
	this->setActive(false);

	this->player = player;
	_bReload = false;
	_hitTime = 0;
	_moveClock = 0;

	//set enemy data
	type = Enum::OwnerType::Enemy;
	_moveSpeed = 3;
	_reloadTime = 1;
	_fireCountdown = 0;
	_bulletSpeed = 10;
	_health = 100;
	_damage = 5;
	
	_currentHealth = _health;
}


void Enemy::update(float dt) 
{
	if (!active) return;

	_clock += dt;
	movement(dt);
	shape->update(dt);
	fire(dt);
	collider->updateCollider(shape->getWorldPosition());


	if (_bHit) {
		_hitTime = _clock;
		this->shape->setColor(vec4(1, 0, 0, 1));
		_bHit = false;
	}
	if (_clock - _hitTime >= 0.1f) {
		this->shape->setColor(selfColor);
		_clock = 0;
	}

	if (_currentHealth <= 0) 
	{
		EnemyController::getInstance()->deadEnemy++;
		EnemyController::getInstance()->enemyInField--;
		setActive(false); 
	}

	if (shape->position.y <= -VP_HALFWIDTH) {
		this->setActive(false);
		EnemyController::getInstance()->enemyInField--;
	}
}


void Enemy::movement(float dt) 
{
	if (!active) return;
	
	_moveClock += dt;
	this->shape->position.y += -_moveSpeed * dt;
	this->shape->position.x = VP_HALFWIDTH / 2 * cos(this->shape->position.y);
	
	if (_moveClock >= 2.0f)_moveClock -= 2.0f;
}


void Enemy::fire(float dt) 
{

	if (_fireCountdown >= _reloadTime)
	{
		_fireCountdown -= _reloadTime;
		_bReload = false;
	}
	else {
		_fireCountdown += dt;
		_bReload = true;
	}

	if (!_bReload) {
		// fire
		BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy,
			this, this->shape->position + vec3(0, -0.5f, 0), normalize(player->position - this->shape->position), vec3(0, 0, 180), 0.8f, _bulletSpeed);
		
	}
}


void Enemy::setActive(bool active) 
{
	//this->collider->setActive(active);
	this->active = active;
}


bool Enemy::isActive() 
{
	return active;
}


void Enemy::init(vec3 initPos, vec3 initRot, float initScale)
{
	this->setActive(true);
	this->shape->position = initPos;
	this->shape->rotation = initRot;
	this->shape->scale = vec3(initScale, initScale, initScale);
	_currentHealth = _health;
}



void Enemy::takeDamage(int damage)
{
	_bHit = true;
	this->_currentHealth -= damage;
}


void Enemy::setSelfColor(vec4 color) 
{
	this->selfColor = color;
	this->shape->setColor(color);
}