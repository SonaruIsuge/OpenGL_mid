#pragma once


#include "Shape.h"


class BossBulletShape :public Shape
{
private:


public:

	BossBulletShape(Shape* parent = nullptr);
	~BossBulletShape();
	void update(float dt);
};