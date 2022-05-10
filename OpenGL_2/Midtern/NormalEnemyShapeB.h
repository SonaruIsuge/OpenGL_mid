#pragma once
#pragma once

#include "Shape.h"


class NormalEnemyShapeB :public Shape
{
private:


public:

	NormalEnemyShapeB(Shape* parent = nullptr);
	~NormalEnemyShapeB();
	void update(float dt);
};