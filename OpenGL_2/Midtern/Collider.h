#pragma once

#include "../Header/Angel.h"


class Collider 
{
private:
	bool ownerActive;

public:
	vec3 center;
	float radius;
	float scale;

	Collider(vec3 center, float redius, float scale);
	~Collider();
	void updateCollider(vec3 center, float scale = 1);
	bool isCollide(Collider* other);

	void setActive(bool active);
	bool isActive();
};