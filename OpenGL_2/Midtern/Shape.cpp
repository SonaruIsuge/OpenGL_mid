
#include "Shape.h"



Shape::Shape(Shape* parent)
{
	_Points = nullptr;
	_Colors = nullptr;
	_nVtx = 0;
	_pVXshader = NULL;
	_pFSshader = NULL;
	_fClock = 0;

	_uiVao = 0;
	_uiBuffer = 0;
	_bUpdateMV = false;
	_bUpdateProj = false;
	_fColor[0] = _fColor[1] = _fColor[2] = _fColor[3] = 1.0f;

	position = vec3(0, 0, 0);
	rotation = vec3(0, 0, 0);
	scale = vec3(1, 1, 1);
	boundsRadius = 0;

	if (parent != nullptr) this->parent = parent;
	else this->parent = nullptr;
}

Shape::~Shape()
{
	if (_Points != nullptr) delete[] _Points;
	if (_Colors != nullptr) delete[] _Colors;

	if (_pVXshader != NULL) delete[] _pVXshader;
	if (_pFSshader != NULL) delete[] _pFSshader;
}


void Shape::init(vec4 vColor, mat4 mxModelView, mat4 mxProjection)
{
	setColor(vColor);
	setShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	setShader(mxModelView, mxProjection);
}


void Shape::CreateBufferObject()
{
	glGenVertexArrays(1, &_uiVao);
	glBindVertexArray(_uiVao);

	// Create and initialize a buffer object

	glGenBuffers(1, &_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, _nVtx * sizeof(vec4) * 2, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, _nVtx * sizeof(vec4), _Points);
	glBufferSubData(GL_ARRAY_BUFFER, _nVtx * sizeof(vec4), _nVtx * sizeof(vec4), _Colors);

}

void Shape::setShader(mat4& mxView, mat4& mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader(_pVXshader, _pFSshader);
	else _uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(_uiProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(_nVtx * sizeof(vec4)));

	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
	_mxView = mxView;
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);

	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
	_mxProjection = mxProjection;
	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Shape::setShaderName(const char vxShader[], const char fsShader[])
{
	int len;
	len = strlen(vxShader);
	_pVXshader = new char[len + 1];
	memcpy(_pVXshader, vxShader, len + 1);

	len = strlen(fsShader);
	_pFSshader = new char[len + 1];
	memcpy(_pFSshader, fsShader, len + 1);
}



void Shape::setViewMatrix(mat4& mat)
{
	_mxView = mat;
}

void Shape::setProjectionMatrix(mat4& mat)
{
	_mxProjection = mat;
	_bUpdateProj = true;
}

//void Shape::setTRSMatrix(mat4& mat)
//{
//	_mxTRS = mat;
//	_bUpdateMV = true;
//}

void Shape::setColor(vec4 vColor)
{
	_fColor[0] = vColor.x; _fColor[1] = vColor.y;
	_fColor[2] = vColor.z; _fColor[3] = vColor.w;

	for (int i = 0; i < _nVtx; i++) {
		_Colors[i].x = _fColor[0];
		_Colors[i].y = _fColor[1];
		_Colors[i].z = _fColor[2];
		_Colors[i].w = _fColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, _nVtx * sizeof(vec4), _nVtx * sizeof(vec4), _Colors);
}


mat4 Shape::getTRSMatrix() 
{
	// TRSMatrix = [T][R][S][P] (2D ¥u¦Ò¼{z¶b±ÛÂà)
	mat4 mt;

	if (parent != nullptr) {
		mt = parent->getTRSMatrix();
	}

	mt = mt * Translate(position) * RotateZ(rotation.z) * Scale(scale);
	
	return mt;
}


vec3 Shape::getWorldPosition() 
{
	vec3 pos = vec3(0, 0, 0);

	if (parent != nullptr) {
		pos = parent->getWorldPosition();
	}

	pos = pos + position;

	return pos;
}


mat4 Shape::getModelViewMatrix() 
{
	return _mxView;
}


mat4 Shape::getProjectionMatrix() 
{
	return _mxProjection;
}

void Shape::draw()
{
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);
	_mxTRS = getTRSMatrix();
	_mxMVFinal = _mxView * _mxTRS;
	
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);

	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _nVtx);
}

void Shape::drawW()
{
	glBindVertexArray(_uiVao);

	_mxTRS = getTRSMatrix();
	_mxMVFinal = _mxView * _mxTRS;
	

	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxMVFinal);
	if (_bUpdateProj) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, _nVtx);
}


