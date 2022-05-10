#pragma once

#include "Shape.h"


class NormalBulletShape :public Shape
{
private:


public:

	NormalBulletShape(Shape* parent = nullptr);
	~NormalBulletShape();
	void update(float dt);
};