
#include "CurveEnemy.h"
#include "BulletManager.h"


CurveEnemy::CurveEnemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player) : Enemy(shape, mxModelView, mxProjection, player) 
{
	p0 = p1 = p2 = p3 = vec3(0, 0, 0);
	_moveClock = 0;
	
	// set enemy data
	type = Enum::OwnerType::Enemy;
	_moveSpeed = 4;
	_reloadTime = 1.2f;
	_fireCountdown = 0;
	_bulletSpeed = 8;
	_health = 200;
	_damage = 10;
	_currentHealth = _health;
	_bulletRadFromBody = 0.2f;

	_moveTime = 2 * VP_HALFWIDTH / _moveSpeed;
}


CurveEnemy::~CurveEnemy() {}


void CurveEnemy::init(vec3 initPos, vec3 initRot, float initScale) 
{
	Enemy::init(initPos, initRot, initScale);
	_moveClock = 0;
	p0 = initPos;
	float rand = EnemyController::getInstance()->random->randFloat(-VP_HALFWIDTH/3, VP_HALFWIDTH/3);
	p1 = vec3(rand, initPos.y + rand, 0);
	p2 = vec3(rand * 2, initPos.y + rand * 2, 0);
	p3 = vec3(initPos.x, -VP_HALFWIDTH - 2, 0);
}


void CurveEnemy::movement(float dt) 
{
	if (!active) return;

	_moveClock += dt;
	float t = _moveClock / _moveTime;
	float u = 1 - t;

	this->shape->position = (u * u * u * p0) + (3 * t * u * u * p1) + (3 * t * t * u * p2) + (t * t * t * p3);

	//if (_moveClock >= _moveTime) _moveClock -= _moveTime;
}


void CurveEnemy::fire(float dt) 
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
		for (int i = 0; i < 12; i++) {
			BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy, 
				this, this->shape->position + vec3(0.2f * cos(30.0 * i * PI / 180), 0.2f * sin(30.0 * i * PI / 180), 0),
				normalize(vec3(cos(30.0 * i * PI / 180), sin(30.0 * i * PI / 180), 0)),
				vec3(0, 0, 30.0f * i), 0.8f, _bulletSpeed);
		}
		
	}
	
}