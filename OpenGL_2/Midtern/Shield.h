#pragma once

#include "Shape.h"
#include "Collider.h"

class Shield {
private:

	bool active;
	float stayTime;
	float stayTimer;
	float scTime;
	float scTimer;

public:

	Shape* shape;
	Collider* collider;

	Shield(Shape* shape, mat4 mxModelView, mat4 mxProjection, Shape* parent);
	~Shield();

	void setActive(bool active);
	bool isActive();
	void updateShield(float dt);
	void drawShield();
};