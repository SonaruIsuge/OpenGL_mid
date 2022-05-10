#include "Collider.h"


Collider::Collider(vec3 center, float radius, float scale) 
{
	this->center = center;
	this->radius = radius;
	this->scale = scale;
	this->ownerActive = false;
}


void Collider::updateCollider(vec3 center, float scale)
{
	if (scale != 1) this->scale = scale;
	this->center = center;
}


bool Collider::isCollide(Collider* other) 
{
	//if (!ownerActive || !other->isActive()) return false;

	vec3 diff = other->center - this->center;
	float distance = length(diff);
	
	return (distance <= this->radius * this->scale + other->radius * other->scale);
}


void Collider::setActive(bool active) { ownerActive = active; }


bool Collider::isActive() { return ownerActive; }


Collider::~Collider() { }