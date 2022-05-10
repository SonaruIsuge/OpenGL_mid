#pragma once


#include "Shape.h"


class BossNShape :public Shape
{
private:


public:

	BossNShape(Shape* parent = nullptr);
	~BossNShape();
	void update(float dt);
};