#include "BossNShape.h"


BossNShape::BossNShape(Shape* parent) : Shape(parent)
{
	_nVtx = 30;

	_Points = new vec4[_nVtx];

	_Points[0] = vec4(-0.5f, 0.0f, 0.0f, 1.0f);
	_Points[1] = vec4(0.0f, 0.5f, 0.0f, 1.0f);
	_Points[2] = vec4(0.5f, 0.0f, 0.0f, 1.0f);

	_Points[3] = vec4(-0.5f, 0.0f, 0.0f, 1.0f);
	_Points[4] = vec4(0.5f, 0.0f, 0.0f, 1.0f);
	_Points[5] = vec4(0.0f, -0.5f, 0.0f, 1.0f);

	_Points[6] = vec4(-0.1f, 0.6f, 0.0f, 1.0f);
	_Points[7] = vec4(0.0f, 0.8f, 0.0f, 1.0f);
	_Points[8] = vec4(0.1f, 0.6f, 0.0f, 1.0f);

	_Points[9] = vec4(-0.1f, 0.6f, 0.0f, 1.0f);
	_Points[10] = vec4(0.1f, 0.6f, 0.0f, 1.0f);
	_Points[11] = vec4(0.0f, 0.5f, 0.0f, 1.0f);

	_Points[12] = vec4(0.6f, 0.1f, 0.0f, 1.0f);
	_Points[13] = vec4(0.8f, 0.0f, 0.0f, 1.0f);
	_Points[14] = vec4(0.6f, -0.1f, 0.0f, 1.0f);

	_Points[15] = vec4(0.6f, 0.1f, 0.0f, 1.0f);
	_Points[16] = vec4(0.6f, -0.1f, 0.0f, 1.0f);
	_Points[17] = vec4(0.5f, 0.0f, 0.0f, 1.0f);

	_Points[18] = vec4(-0.1f, -0.6f, 0.0f, 1.0f);
	_Points[19] = vec4(0.0f, -0.5f, 0.0f, 1.0f);
	_Points[20] = vec4(0.1f, -0.6f, 0.0f, 1.0f);

	_Points[21] = vec4(-0.1f, -0.6f, 0.0f, 1.0f);
	_Points[22] = vec4(0.1f, -0.6f, 0.0f, 1.0f);
	_Points[23] = vec4(0.0f, -0.8f, 0.0f, 1.0f);

	_Points[24] = vec4(-0.6f, 0.1f, 0.0f, 1.0f);
	_Points[25] = vec4(-0.5f, 0.0f, 0.0f, 1.0f);
	_Points[26] = vec4(-0.6f, -0.1f, 0.0f, 1.0f);

	_Points[27] = vec4(-0.6f, 0.1f, 0.0f, 1.0f);
	_Points[28] = vec4(-0.6f, -0.1f, 0.0f, 1.0f);
	_Points[29] = vec4(-0.8f, 0.0f, 0.0f, 1.0f);


	_Colors = new vec4[_nVtx];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[6] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[7] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[8] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[9] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[10] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[11] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[12] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[13] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[14] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[15] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[16] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[17] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[18] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[19] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[20] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[21] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[22] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[23] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[24] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[25] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[26] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[27] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[28] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[29] = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;

	boundsRadius = 0.8f;

	if (parent != nullptr) this->parent = parent;
	else this->parent = nullptr;
}


BossNShape::~BossNShape() {}


void BossNShape::update(float dt)
{

}

