#pragma once

#include "Shape.h"


class PlayerShapeA :public Shape
{
private:


public:

	PlayerShapeA(Shape* parent = nullptr);
	~PlayerShapeA();
	void update(float dt);
};