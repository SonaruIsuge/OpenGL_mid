
#include "BigEnemy.h"
#include "BulletManager.h"


BigEnemy::BigEnemy(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* player) : Enemy(shape, mxModelView, mxProjection, player)
{
	initPos = vec3(0, 0, 0);

	// set enemy data
	type = Enum::OwnerType::Enemy;
	_reloadTime = 1.0f;
	_fireCountdown = 0;
	_bulletSpeed = 4;
	_health = 700;
	_damage = 10;
	_moveSpeed = 6;
	_currentHealth = _health;

	fireNumPerReload = 6;
	fireCount = 0;
	shortReloadTime = 0.3f;
	_timer = 0;
	_moveXTimer = 0;
	reverse = false;
}


BigEnemy::~BigEnemy() {}


void BigEnemy::init(vec3 initPos, vec3 initRot, float initScale) 
{
	Enemy::init(initPos, initRot, initScale);
	this->initPos = initPos;
	_moveXTimer = 0;
}


void BigEnemy::movement(float dt)
{
	if (!active) return;

	_moveXTimer += dt;
	reverse = this->shape->position.x > 0;
	
	this->shape->position.x = initPos.x + 0.4 * cosf(_moveXTimer);

	if (shape->position.y <= VP_HALFWIDTH * 0.7) return;

	this->shape->position.y += (-4 * dt);

	if (_moveXTimer >= 0.4 * VP_HALFWIDTH / _moveSpeed) _moveXTimer -= 0.4 * VP_HALFWIDTH / _moveSpeed;
}


void BigEnemy::fire(float dt)
{
	_fireCountdown += dt;
	if (_fireCountdown >= _reloadTime) {
		//fire
		_timer += dt;
		if (_timer >= shortReloadTime && fireCount < fireNumPerReload) {
			if (!reverse) {
				for (int i = 0; i < 9; i++) {
					float angle = 15.0f * i;
					BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy, this, 
						this->shape->position + vec3(0.2f * cosf((270 + angle) * PI / 180), 0.2f * sinf((270 + angle) * PI / 180), 0),
						normalize(vec3(cosf((270 + angle) * PI / 180), sinf((270 + angle) * PI / 180), 0)),
						vec3(0, 0, (270 + angle)), 0.8f, _bulletSpeed);
				}
			}
			else {
				for (int i = 0; i < 9; i++) {
					float angle = 15.0f * i;
					BulletManager::getInstance()->fire(Enum::BulletType::NormalEnemy, this, 
						this->shape->position + vec3( 0.2f * cosf((180 + angle) * PI / 180), 0.2f * sinf((180 + angle) * PI / 180), 0 ),
						normalize(vec3( cosf((180 + angle) * PI / 180), sinf((180 + angle) * PI / 180), 0 )),
						vec3(0, 0, (180 + angle)), 0.8f, _bulletSpeed);
				}
			}
			_timer -= shortReloadTime;
			fireCount++;
		}
		else if (fireCount >= fireNumPerReload) {
			_fireCountdown -= (_reloadTime + shortReloadTime * fireCount + _timer);
			fireCount = 0;
		}
	}
}