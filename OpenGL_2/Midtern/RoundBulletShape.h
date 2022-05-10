#pragma once

#include "Shape.h"


class RoundBulletShape :public Shape
{
private:


public:

	RoundBulletShape(Shape* parent = nullptr);
	~RoundBulletShape();
	void update(float dt);
};