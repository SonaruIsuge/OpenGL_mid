

#include "EnemyController.h"
#include "NormalEnemyShapeA.h"
#include "NormalEnemyShapeB.h"
#include "BossNShape.h"


EnemyController* EnemyController::_instance = nullptr;


EnemyController* EnemyController::getInstance() 
{
	if (_instance == nullptr)
	{
		_instance = new EnemyController;
	}

	return _instance;
}


EnemyController::EnemyController() 
{
	
}


EnemyController::~EnemyController() 
{
	
}


void EnemyController::init(Character* player, mat4 mxModelView, mat4 mxProjection)
{
	random = new Random;
	this->player = player;

	_clock = 0;
	_enemyInitCooldown = 5;
	_cooldownTimer = 0;

	_currentWave = 1;
	_maxEnemyNum = 20;

	enemyInField = 0;
	deadEnemy = 0;

	killedBigEnemy = 0;
	_isBossAppear = true;

	for (int i = 0; i < _maxEnemyNum; i++) {
		Enemy* enemy = new Enemy(new NormalEnemyShapeA, mxModelView, mxProjection, player->shape);
		enemies.init(enemy);

		Enemy* curveEnemy = new CurveEnemy(new NormalEnemyShapeA, mxModelView, mxProjection, player->shape);
		curveEnemies.init(curveEnemy);
	}
	// only two bigEnemy
	Enemy* bigEnemy = new BigEnemy(new NormalEnemyShapeB, mxModelView, mxProjection, player->shape);
	bigEnemies.init(bigEnemy);
	bigEnemy = new BigEnemy(new NormalEnemyShapeB, mxModelView, mxProjection, player->shape);
	bigEnemies.init(bigEnemy);

	// one boss
	boss = new Boss(new BossNShape, mxModelView, mxProjection, player->shape);
}


void EnemyController::draw() 
{
	Node<Enemy>* current = enemies.using_first;
	while (current != nullptr) {
		current->data->shape->draw();
		current = current->next;
	}

	current = curveEnemies.using_first;
	while (current != nullptr) {
		current->data->shape->draw();
		current = current->next;
	}

	current = bigEnemies.using_first;
	while (current != nullptr) {
		current->data->shape->draw();
		current = current->next;
	}
	if (_isBossAppear && boss->isActive()) boss->shape->draw();
}


void EnemyController::update(float dt) 
{
	updateEnemyPerform(dt);
	//updateEnemyInit(dt);

	Node<Enemy>* current = enemies.using_first;
	while (current != nullptr) {
		
		current->data->update(dt);

		ColliderControl(current->data);

		if (!current->data->isActive()) {

			enemies.recycleNode(current);
		}

		current = current->next;
	}
	//printf("%d , %d\n", enemies.getLength(), enemies.getUsingLength());

	current = curveEnemies.using_first;
	while (current != nullptr) {

		current->data->update(dt);

		ColliderControl(current->data);

		if (!current->data->isActive()) {

			curveEnemies.recycleNode(current);
		}

		current = current->next;
	}

	current = bigEnemies.using_first;
	while (current != nullptr) {

		current->data->update(dt);

		ColliderControl(current->data);

		if (!current->data->isActive()) {

			bigEnemies.recycleNode(current);
			killedBigEnemy++;
		}

		current = current->next;
	}

	if (_isBossAppear) boss->update(dt);
}


void EnemyController::updateEnemyPerform(float dt) 
{
	
	switch (_currentWave)
	{
	case 1:
		//setBossFight(dt);
		SetWave1Perform(dt, 1, 20);
		if (deadEnemy >= 30) _currentWave++;
		break;

	case 2:
		SetWave2Perform(dt, 1.5, 10);
		if (deadEnemy >= 50) { 
			_currentWave++; 
			_clock = 0;
		}
		break;

	case 3:
		SetWave3Perform(dt, 4, 15);
		if (killedBigEnemy == 2) _currentWave++;
		break;

	case 4:
		_isBossAppear = true;
		setBossFight(dt);
	default:
		break;
	}
}


void EnemyController::ColliderControl(Enemy* enemy) 
{
	if (enemy->collider->isCollide(player->collider)) {
		enemy->takeDamage(player->getDamage());
		player->takeDamage(enemy->getDamage());
	}
}


void EnemyController::destroy() {
	if (_instance != nullptr) delete _instance;
}



// --------------------------------------------------------------------------------
// Game Perform
void EnemyController::SetWave1Perform(float dt, float initCooldown, int maxEnemy)
{
	if (enemyInField >= maxEnemy) return;

	_cooldownTimer += dt;

	if (_cooldownTimer >= initCooldown)
	{
		Node<Enemy>* enemy = enemies.getNode();
		if (enemy == nullptr) return;
		enemyInField++;
		enemy->data->init(vec3(random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		enemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		_cooldownTimer -= initCooldown;
	}
}


void EnemyController::SetWave2Perform(float dt, float initCooldown, int maxEnemy)
{
	if (enemyInField >= maxEnemy) return;

	_cooldownTimer += dt;

	if (_cooldownTimer >= initCooldown)
	{
		Node<Enemy>* enemy = curveEnemies.getNode();
		if (enemy == nullptr) return;
		enemyInField++;
		enemy->data->init(vec3(random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		enemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		_cooldownTimer -= initCooldown;
	}
}


void EnemyController::SetWave3Perform(float dt, float initCooldown, int maxEnemy)
{
	if (enemyInField >= maxEnemy) return;
	
	if (_clock == 0) {
		Node<Enemy>* bigEnemy = bigEnemies.getNode();
		if (bigEnemy == nullptr) return;
		bigEnemy->data->init(vec3(-VP_HALFWIDTH* 0.7f, VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		bigEnemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		enemyInField++;

		bigEnemy = bigEnemies.getNode();
		if (bigEnemy == nullptr) return;
		enemyInField++;
		bigEnemy->data->init(vec3(VP_HALFWIDTH * 0.7f, VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		bigEnemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		
	}
	if (_cooldownTimer >= initCooldown)
	{
		Node<Enemy>* enemy = enemies.getNode();
		if (enemy == nullptr) return;
		enemyInField++;
		enemy->data->init(vec3(0, VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		enemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		_cooldownTimer -= initCooldown;
	}
	if (_clock >= initCooldown* 1.5f)
	{
		Node<Enemy>* enemy = curveEnemies.getNode();
		if (enemy == nullptr) return;
		enemyInField++;
		enemy->data->init(vec3(random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), VP_HALFWIDTH + 1, 0), vec3(0, 0, 0), 1);
		enemy->data->setSelfColor(vec4(random->rand01(), random->rand01(), random->rand01(), 1));
		_clock -= initCooldown;
	}
	_cooldownTimer += dt;
	_clock += dt;

}


void EnemyController::setBossFight(float dt) 
{
	boss->init(vec3(0, VP_HALFWIDTH * 0.7, 0), vec3(0, 0, 0), 1);
}