#pragma once

#include "Shape.h"


class PlayerShapeC :public Shape
{
private:


public:

	PlayerShapeC(Shape* parent = nullptr);
	~PlayerShapeC();
	void update(float dt);
};