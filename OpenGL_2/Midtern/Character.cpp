
#include "Character.h"


Character::Character()
{
	shape = nullptr;
	collider = nullptr;
	_clock = 0;
	_bHit = false;
}


Character::~Character() 
{
	if (shape != nullptr) delete shape;
	if (collider != nullptr) delete collider;
}



void Character::resetTransform()
{
	//mat4 mt = Translate(0, 0, 0);
	this->shape->position = vec3(0, 0, 0);
	this->shape->rotation = vec3(0, 0, 0);
	this->shape->scale = vec3(1, 1, 1);
}


void Character::changeShape(Shape* oldShape, Shape* newShape)
{
	//printf("change");
	this->shape = newShape;
	
	mat4 mxViewModel = oldShape->getModelViewMatrix();
	mat4 mxProjection = oldShape->getProjectionMatrix();
	vec4 vColor = vec4(1, 1, 0, 1);
	newShape->init(vColor, mxViewModel, mxProjection);
	newShape->position = oldShape->position;
	newShape->rotation = oldShape->rotation;
	newShape->scale = oldShape->scale;
}


Enum::OwnerType Character::getType() { return type; }


int Character::getHealth() { return _currentHealth; }

float Character::getHealthPercent() { return (float)_currentHealth / (float)_health; }

int Character::getDamage() { return _damage; }

