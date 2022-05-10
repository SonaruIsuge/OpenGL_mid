#pragma once

#include "Shape.h"


class NormalEnemyShapeA :public Shape
{
private:


public:

	NormalEnemyShapeA(Shape* parent = nullptr);
	~NormalEnemyShapeA();
	void update(float dt);
};