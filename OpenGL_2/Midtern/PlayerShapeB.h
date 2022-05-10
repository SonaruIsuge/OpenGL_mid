#pragma once

#include "Shape.h"


class PlayerShapeB :public Shape
{
private:


public:

	PlayerShapeB(Shape* parent = nullptr);
	~PlayerShapeB();
	void update(float dt);
};