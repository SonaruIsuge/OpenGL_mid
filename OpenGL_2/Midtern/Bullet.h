#pragma once

#include "../Header/Angel.h"
#include "Character.h"
#include "Shape.h"
#include "Collider.h"
#include "Enum.h"
#include "ObjectPool.h"


class Bullet 
{
private:
	float _timer;
	float _recycleTime;
	bool active;
	

protected:

	float moveSpeed;
	vec3 direction;
	vec4 selfColor;
	

public:
	int damage;

	Shape* shape;
	Collider* collider;	
	Enum::OwnerType owner;
	ObjectPool<Bullet>* poolParent;

	Bullet(Shape* shape, mat4 mxModelView, mat4 mxProjection);
	~Bullet();

	void fire(vec3 position, vec3 direction, vec3 rotation, float scale, float moveSpeed);
	void draw();
	void update(float dt);
	void setActive(bool active);
	void setOwner(Character* owner);
	void setShape(Shape* oldShape, Shape* newShape);
	void setRecycleTime(float recycleTime);
	float calRecycleTime(vec3 pos, vec3 dir, float speed);
	bool isActive();
	void setSelfColor(vec4 color);
	void resetData();
};