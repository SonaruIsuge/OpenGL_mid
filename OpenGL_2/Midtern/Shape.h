#pragma once

#include "../header/Angel.h"

#define PI 3.1415926f
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2)
#define VP_HALFWIDTH  12.0f

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Shape
{
protected:
	char* _pVXshader, * _pFSshader;
	GLfloat _fColor[4];
	GLfloat _fClock;

	//  for Shader
	GLuint _uiProgram;
	// Vertex Position Attribute
	GLuint _uiModelView, _uiProjection;


	// VAO
	GLuint _uiVao;
	// VBO
	GLuint _uiBuffer;


	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;


public:
	vec4* _Points;		
	vec4* _Colors;		

	int  _nVtx;			 

	vec3 position;
	vec3 rotation;
	vec3 scale;

	float boundsRadius;

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	// 父子關係
	Shape* parent;


	void CreateBufferObject();

	Shape(Shape* parent = nullptr);
	virtual ~Shape();
	void init(vec4 vColor, mat4 mxModelView, mat4 mxProjection);

	virtual void update(float dt) = 0;

	void setShaderName(const char vxShader[], const char fsShader[]);
	void setShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint getShaderHandle() { return _uiProgram; }
	
	void setViewMatrix(mat4& mat);
	void setProjectionMatrix(mat4& mat);
	//void setTRSMatrix(mat4& mat);
	void setColor(vec4 vColor); // Single color

	mat4 getTRSMatrix();
	vec3 getWorldPosition();
	mat4 getModelViewMatrix();
	mat4 getProjectionMatrix();

	void draw();
	void drawW(); // Drawing without setting shaders

};


