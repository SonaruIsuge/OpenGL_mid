#pragma once


#include "Shape.h"


class BossAShape :public Shape
{
private:


public:

	BossAShape(Shape* parent = nullptr);
	~BossAShape();
	void update(float dt);
};