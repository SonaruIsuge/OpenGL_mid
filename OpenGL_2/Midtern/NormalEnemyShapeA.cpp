#include "NormalEnemyShapeA.h"


NormalEnemyShapeA::NormalEnemyShapeA(Shape* parent) : Shape(parent)
{
	_nVtx = 6;

	_Points = new vec4[_nVtx];

	_Points[0] = vec4( 0.0f,  0.5f, 0.0f, 1.0f);
	_Points[1] = vec4( 0.5f,  0.0f, 0.0f, 1.0f);
	_Points[2] = vec4( 0.0f, -0.5f, 0.0f, 1.0f);
	_Points[3] = vec4( 0.0f,  0.5f, 0.0f, 1.0f);
	_Points[4] = vec4( 0.0f, -0.5f, 0.0f, 1.0f);
	_Points[5] = vec4(-0.5f,  0.0f, 0.0f, 1.0f);

	_Colors = new vec4[_nVtx];
	_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1] = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4] = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5] = vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;

	boundsRadius = 0.5f;

	if (parent != nullptr) this->parent = parent;
	else this->parent = nullptr;
}


NormalEnemyShapeA::~NormalEnemyShapeA() {}


void NormalEnemyShapeA::update(float dt)
{

}
