#include "Player.h"
#include "InputManager.h"
#include "BulletManager.h"
#include "EnemyController.h"
#include "PlayerShapeA.h"
#include "PlayerShapeB.h"
#include "PlayerShapeC.h"
#include "ShieldShape.h"


Player::Player(Shape* shape, mat4 mxModelView, mat4 mxProjection)
{
	random = new Random;
	vec4 vColor = vec4(1, 1, 0, 1);

	this->shape = shape;
	this->shape->init(vColor, mxModelView, mxProjection);

	this->collider = new Collider(shape->getWorldPosition(), shape->boundsRadius, 1);
	this->shield = new Shield(new ShieldShape, mxModelView, mxProjection, this->shape);

	_bReload = false;
	_bEnableFire = false;
	_canLevelUp = false;
	_bATField = false;
	_hitTime = 0;

	// set player data
	level = 1;
	type = Enum::OwnerType::Player;
	_reloadTime = 0.05f;
	_fireCountdown = 0;
	_bulletSpeed = 16;
	_health = 100;
	_damage = 10;
	_currentHealth = _health;
}


void Player::init(vec3 initPos, vec3 initRot, float initScale)
{
	this->shape->position = initPos;
	this->shape->rotation = initRot;
	this->shape->scale = vec3(initScale, initScale, initScale);
	_currentHealth = _health;
	this->collider->setActive(true);
}


void Player::draw() 
{
	this->shape->draw();
	this->shield->drawShield();
}


void Player::update(float dt) 
{
	_clock += dt;
	movement(dt);
	shape->update(dt);
	fire(dt);
	collider->updateCollider(shape->getWorldPosition());

	shieldControl();
	shield->updateShield(dt);

	levelManage();

	if (_bHit) {
		_hitTime = _clock;
		this->shape->setColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		_bHit = false;
	}
	if (_clock - _hitTime >= 0.1f) {
		this->shape->setColor(vec4(1, 1, 0, 1));
		_clock = 0;
	}
}


void Player::movement(float dt) 
{
	GLfloat tx = 12.0f * (InputManager::getInstance()->getMouseX() - HALF_SIZE) / (HALF_SIZE);
	GLfloat ty = -12.0f * (InputManager::getInstance()->getMouseY() - HALF_SIZE) / (HALF_SIZE);
	this->shape->position = vec3(tx, ty, 0);
}


void Player::fire(float dt) 
{
	if (!_bEnableFire) return;

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
		firePower(dt, level);
	}
}


void Player::EnableFire(bool b) 
{
	_bEnableFire = b;
}



void Player::takeDamage(int damage)
{
	_bHit = true;
	this->_currentHealth -= damage;
}


void Player::levelManage() 
{
	switch (level)
	{
	case 1:
	default:
		if (EnemyController::getInstance()->deadEnemy >= 25)
		{
			this->changeShape(this->shape, new PlayerShapeB);
			this->shield->shape->parent = this->shape;
			level++;
		}
		break;
	case 2:
		if (EnemyController::getInstance()->deadEnemy >= 50)
		{
			this->changeShape(this->shape, new PlayerShapeC);
			this->shield->shape->parent = this->shape;
			level++;
		}
		break;

	case 3:

		break;
	}
	
}


void Player::firePower(float dt, int num) 
{
	switch (num)
	{
	case 1:
		BulletManager::getInstance()->fire(Enum::BulletType::NormalPlayer,
			this, this->shape->position + vec3(0, 1, 0), vec3(0, 1, 0), vec3(0, 0, 0), 1, _bulletSpeed);
		break;

	case 2:
		for (int i = 0; i < 2; i++) {
			BulletManager::getInstance()->fire(Enum::BulletType::NormalPlayer,
				this, this->shape->position + vec3(-0.25f + 0.5f * i, 1, 0), vec3(-0.09f + 0.18f * i, 1, 0), vec3(0, 0, 5 + -10 * i), 1, _bulletSpeed);
		}
		break;

	case 3:
		for (int i = 0; i < 3; i++) {
			BulletManager::getInstance()->fire(Enum::BulletType::NormalPlayer,
				this, this->shape->position + vec3(-0.25f + 0.25f * i, 1, 0), vec3(-0.09f + 0.09f * i, 1, 0), vec3(0, 0, 5 + -5 * i), 1, _bulletSpeed);
		}
		break;

	default:
		break;
	}
}


void Player::shieldControl() 
{
	_bATField = shield->isActive();

	if (!_bATField) {
		if (InputManager::getInstance()->isKeyClick(32)) {
			//printf("ATField!\n");
			shield->setActive(true);
		}
	}
}