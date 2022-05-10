

#include "BulletManager.h"
#include "NormalBulletShape.h"
#include "RoundBulletShape.h"
#include "BossBulletShape.h"
#include "Player.h"

BulletManager* BulletManager::_instance = nullptr;


BulletManager* BulletManager::getInstance() 
{
	if (_instance == nullptr)
	{
		_instance = new BulletManager;
	}

	return _instance;
}


BulletManager::BulletManager() 
{

}



BulletManager::~BulletManager() 
{
	
}


void BulletManager::init(Character* player, mat4 mxModelView, mat4 mxProjection, int size)
{
	random = new Random;
	this->player = player;

	_recycleTimer = 3;
	for (int i = 0; i < size; i++) {
		Bullet* newBullet = new Bullet(new NormalBulletShape, mxModelView, mxProjection);
		newBullet->setRecycleTime(4);
		//newBullet->poolParent = &bulletPool;
		bulletPool.init(newBullet);
	}
	for (int i = 0; i < size * 2; i++) {
		Bullet* newBullet = new Bullet(new RoundBulletShape, mxModelView, mxProjection);
		newBullet->setRecycleTime(8);
		//newBullet->poolParent = &enemyBulletPool;
		enemyBulletPool.init(newBullet);
	}
	for (int i = 0; i < size * 2; i++) {
		Bullet* newBullet = new Bullet(new BossBulletShape, mxModelView, mxProjection);
		newBullet->setRecycleTime(8);
		//newBullet->poolParent = &enemyBulletPool;
		bossBulletPool.init(newBullet);
	}
}


void BulletManager::fire(Enum::BulletType BulletType, Character* owner, vec3 origin, vec3 direction, vec3 rotation, float scale, float speed)
{
	switch (BulletType)
	{
	case Enum::BulletType::NormalPlayer:
		{
			Node<Bullet>* node = bulletPool.getNode();
			
			if (node == nullptr) return;

			node->data->setOwner(owner);
			node->data->setSelfColor(PLAYER_BULLET_COLOR);
			node->data->fire(origin, direction, rotation, scale, speed);
		}
		break;

	case Enum::BulletType::NormalEnemy:
		{
			Node<Bullet>* node = enemyBulletPool.getNode();

			if (node == nullptr) return;

			node->data->setOwner(owner);
			node->data->setSelfColor(ENEMY_BULLET_COLOR);
			node->data->fire(origin, direction, rotation, scale, speed);
		}
		break;

	case Enum::BulletType::Boss:
		{
			Node<Bullet>* node = bossBulletPool.getNode();

			if (node == nullptr) return;

			node->data->setOwner(owner);
			node->data->setSelfColor(BOSS_BULLET_COLOR);
			node->data->fire(origin, direction, rotation, scale, speed);
		}
		break;
	}
}


void BulletManager::draw() {
	Node<Bullet>* node = bulletPool.using_first;
	while (node != nullptr) {
		node->data->draw();
		node = node->next;
	}

	Node<Bullet>* e_node = enemyBulletPool.using_first;
	while (e_node != nullptr) {
		e_node->data->draw();
		e_node = e_node->next;
	}

	Node<Bullet>* b_node = bossBulletPool.using_first;
	while (b_node != nullptr) {
		b_node->data->draw();
		b_node = b_node->next;
	}
}


void BulletManager::update(float dt) {
	Node<Bullet>* node = bulletPool.using_first;
	while (node != nullptr) {
		node->data->update(dt);
		colliderUpdate(node);

		// pool recycle
		if (!(node->data->isActive())) { 
			node->data->resetData();
			bulletPool.recycleNode(node);
		}

		node = node->next;
	}
	printf("(%d , %d) ", bulletPool.getLength(), bulletPool.getUsingLength());


	Node<Bullet>* e_node = enemyBulletPool.using_first;
	while (e_node != nullptr) {
		e_node->data->update(dt);
		colliderUpdate(e_node);

		// pool recycle
		if (!(e_node->data->isActive())) {
			e_node->data->resetData();
			enemyBulletPool.recycleNode(e_node);
		}

		e_node = e_node->next;
	}
	printf("(%d , %d) ", enemyBulletPool.getLength(), enemyBulletPool.getUsingLength());

	Node<Bullet>* b_node = bossBulletPool.using_first;
	while (b_node != nullptr) {
		b_node->data->update(dt);
		colliderUpdate(b_node);

		// pool recycle
		if (!(b_node->data->isActive())) {
			b_node->data->resetData();
			bossBulletPool.recycleNode(b_node);
		}

		b_node = b_node->next;
	}
	printf("(%d , %d) \n", bossBulletPool.getLength(), bossBulletPool.getUsingLength());
}


void BulletManager::destroy() 
{
	if (_instance != nullptr) delete _instance;
}


void BulletManager::colliderUpdate(Node<Bullet>* node) 
{
	if (node->data->owner == Enum::OwnerType::Enemy) {

		if (((Player*)player)->shield->isActive() && node->data->collider->isCollide(((Player*)player)->shield->collider)) {
			node->data->setActive(false);
		}
		else if(node->data->collider->isCollide(player->collider)){
			// enemy bullet hit player
			player->takeDamage(node->data->damage);
			node->data->setActive(false);
		}
	}
	else if (node->data->owner == Enum::OwnerType::Player)
	{
		//Enemy
		Node<Enemy>* target = EnemyController::getInstance()->enemies.using_first;
		while (target != nullptr) 
		{
			if (node->data->collider->isCollide(target->data->collider)) {
				// player bullet hit target enemy
				target->data->takeDamage(node->data->damage);
				node->data->setActive(false);
			}

			target = target->next;
		}

		//CurveEnemy
		target = EnemyController::getInstance()->curveEnemies.using_first;
		while (target != nullptr)
		{
			if (node->data->collider->isCollide(target->data->collider)) {
				// player bullet hit target enemy
				target->data->takeDamage(node->data->damage);
				node->data->setActive(false);
			}

			target = target->next;
		}

		//BigEnemy
		target = EnemyController::getInstance()->bigEnemies.using_first;
		while (target != nullptr)
		{
			if (node->data->collider->isCollide(target->data->collider)) {
				// player bullet hit target enemy
				target->data->takeDamage(node->data->damage);
				node->data->setActive(false);
			}

			target = target->next;
		}

		//Boss
		Enemy* boss = EnemyController::getInstance()->boss;
		if (boss->isActive() && node->data->collider->isCollide(boss->collider)) {
			// player bullet hit boss

			boss->takeDamage(node->data->damage);
			node->data->setActive(false);
		}
	}
}