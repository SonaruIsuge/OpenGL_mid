#pragma once

#include "Shape.h"


class BossFShape :public Shape
{
private:


public:

	BossFShape(Shape* parent = nullptr);
	~BossFShape();
	void update(float dt);
};