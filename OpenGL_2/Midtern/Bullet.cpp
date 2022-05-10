

#include "Bullet.h"

Bullet::Bullet(Shape* shape, mat4 mxModelView, mat4 mxProjection)
{
	
	_timer = 0.0f;
	_recycleTime = 8.0f;
	moveSpeed = 0.0f;

	selfColor = vec4(1, 0, 0, 1);
	this->shape = shape;
	this->shape->init(selfColor, mxModelView, mxProjection);

	this->collider = new Collider(shape->position, shape->boundsRadius, 1);
	setActive(false);
}


// call when fire bullet
void Bullet::fire(vec3 position, vec3 direction, vec3 rotation, float scale, float moveSpeed)
{
	this->shape->position = position;
	this->shape->rotation = rotation;
	this->shape->scale = vec3(scale, scale, scale);
	this->direction = direction;
	this->moveSpeed = moveSpeed;
	//setRecycleTime(calRecycleTime(position, direction, moveSpeed));
	this->setActive(true);
	_timer = 0.0f;
}


void Bullet::draw() 
{
	if(active) this->shape->draw();
}


void Bullet::update(float dt) 
{
	_timer += dt;
	if (_timer >= _recycleTime) {
		setActive(false);
		
	}
	if (active) {
		this->shape->position += direction * moveSpeed * dt;
		collider->updateCollider(shape->getWorldPosition());

		//if ((this->shape->position.y > VP_HALFWIDTH) || (this->shape->position.y < -VP_HALFWIDTH))
	}
}


Bullet::~Bullet() 
{
	if (shape != nullptr) delete shape;
	if (collider != nullptr) delete collider;
}


void Bullet::setActive(bool active) {
	//this->collider->setActive(active);
	this->active = active;
}


bool Bullet::isActive() {
	return this->active; 
}


void Bullet::setOwner(Character* owner)
{
	this->owner = owner->getType();
	this->damage = owner->getDamage();
}


void Bullet::setShape(Shape* oldShape, Shape* newShape)
{
	this->shape = newShape;
	mat4 mxViewModel = oldShape->getModelViewMatrix();
	mat4 mxProjection = oldShape->getProjectionMatrix();
	vec4 vColor = vec4(1, 1, 0, 1);
	newShape->init(vColor, mxViewModel, mxProjection);
	newShape->position = oldShape->position;
	newShape->rotation = oldShape->rotation;
	newShape->scale = oldShape->scale;
}


void Bullet::setSelfColor(vec4 color)
{
	this->selfColor = color;
	this->shape->setColor(color);
}


void Bullet::setRecycleTime(float recycleTime) 
{
	this->_recycleTime = recycleTime;
}


float Bullet::calRecycleTime(vec3 pos, vec3 dir, float speed)
{
	
	float tX = ( ( VP_HALFWIDTH * (dir.x >= 0 ? 1 : -1) ) - pos.x ) / (dir.x * speed);
	float tY = ( ( VP_HALFWIDTH * (dir.y >= 0 ? 1 : -1) ) - pos.y ) / (dir.y * speed);
	
	//printf("%f\n", tX <= tY ? tX : tY);
	return tX <= tY ? tX : tY;
}

void Bullet::resetData() 
{
	this->shape->position = vec3(0,0,0);
	this->shape->rotation = vec3(0, 0, 0);
	this->shape->scale = vec3(0, 0, 0);
	this->direction = vec3(0, 0, 0);
	this->moveSpeed = 0;
	this->_timer = 0.0f;
}