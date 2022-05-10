#pragma once

#include "Shape.h"


class ShieldShape :public Shape
{
private:


public:

	ShieldShape(Shape* parent = nullptr);
	~ShieldShape();
	void update(float dt);
};