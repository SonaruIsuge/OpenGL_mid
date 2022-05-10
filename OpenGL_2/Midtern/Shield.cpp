

#include "Shield.h"


Shield::Shield(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* parent)
{
	vec4 vColor = vec4(1, 1, 0, 1);

	this->shape = shape;
	this->shape->init(vColor, mxModelView, mxProjection);
	this->shape->parent = parent;
	this->collider = new Collider(shape->getWorldPosition(), shape->boundsRadius, 1);

	setActive(false);
	stayTime = 3;
	stayTimer = 0;
	scTime = 1;
	scTimer = 0;
}

Shield::~Shield() 
{

}


void Shield::drawShield() 
{
	if (!active) return;

	this->shape->draw();
}


void Shield::updateShield(float dt) 
{
	if (!active) return;
	stayTimer += dt;

	shape->update(dt);
	collider->updateCollider(shape->getWorldPosition(), this->shape->scale.y);

	if (stayTimer >= stayTime) {
		scTimer += dt;
		float sc = (VP_HALFWIDTH * 2 / this->collider->radius) * scTimer / scTime;
		shape->scale = vec3(sc, sc, sc);
	}
	if (scTimer >= scTime) {
		setActive(false);
		this->shape->scale = vec3(1, 1, 1);
		this->collider->scale = 1;
		stayTimer = 0;
		scTimer = 0;
	}
}


void Shield::setActive(bool active) 
{
	//this->collider->setActive(active);
	this->active = active;
}


bool Shield::isActive() 
{
	return active;
}