#include "NormalBulletShape.h"


NormalBulletShape::NormalBulletShape(Shape* parent) : Shape(parent)
{
	_nVtx = 12;

	_Points = new vec4[_nVtx];

	//0 3 6 9
	//1 11
	//2 4
	//5 7
	//8
	//10
	_Points[0]  = vec4( 0.0f, -0.3f, 0.0f, 1.0f);
	_Points[1]  = vec4(-0.2f,  0.0f, 0.0f, 1.0f);
	_Points[2]  = vec4( 0.0f,  0.3f, 0.0f, 1.0f);
	_Points[3]  = vec4( 0.0f, -0.3f, 0.0f, 1.0f);
	_Points[4]  = vec4( 0.0f,  0.3f, 0.0f, 1.0f);
	_Points[5]  = vec4( 0.2f,  0.0f, 0.0f, 1.0f);
	_Points[6]  = vec4( 0.0f, -0.3f, 0.0f, 1.0f);
	_Points[7]  = vec4( 0.2f,  0.0f, 0.0f, 1.0f);
	_Points[8]  = vec4( 0.1f, -1.0f, 0.0f, 1.0f);
	_Points[9]  = vec4( 0.0f, -0.3f, 0.0f, 1.0f);
	_Points[10] = vec4(-0.1f, -1.0f, 0.0f, 1.0f);
	_Points[11] = vec4(-0.2f,  0.0f, 0.0f, 1.0f);

	_Colors = new vec4[_nVtx];
	_Colors[0]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	_Colors[1]  = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	_Colors[2]  = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[3]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[4]  = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	_Colors[5]  = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_Colors[6]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[7]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[8]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[9]  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[10] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	_Colors[11] = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Create and initialize a buffer object 
	CreateBufferObject();
	_bUpdateProj = false;

	boundsRadius = 0.3f;

	if (parent != nullptr) this->parent = parent;
	else this->parent = nullptr;
}


NormalBulletShape::~NormalBulletShape() {}


void NormalBulletShape::update(float dt)
{

}
