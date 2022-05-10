#pragma once
#include "Shape.h"
#include "Random.h"

#define BG_OBJ_NUM 50

class Background 
{
private:
	Random* random;
	Shape* bgObjs[BG_OBJ_NUM];

	float minMoveSpeed;
	float maxMoveSpeed;
	float speed[BG_OBJ_NUM];

public:

	Background(mat4 mxModelView, mat4 mxProjection);
	~Background();

	void draw();
	void update(float dt);

};