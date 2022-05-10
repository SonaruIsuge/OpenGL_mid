
#include "Background.h"
#include "NormalEnemyShapeA.h"

#define BACKGROUND_OBJECT_COLOR vec4(1.0f, 1.0f, 0.94f, 1.0f)

Background::Background(mat4 mxModelView, mat4 mxProjection)
{
	random = new Random;

	maxMoveSpeed = 3;
	minMoveSpeed = 0.5;

	for (int i = 0; i < BG_OBJ_NUM; i++) {
		bgObjs[i] = new NormalEnemyShapeA;
		bgObjs[i]->init(BACKGROUND_OBJECT_COLOR, mxModelView, mxProjection);
		bgObjs[i]->position = vec3(random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), random->randFloat(-VP_HALFWIDTH, VP_HALFWIDTH), 0);

		float randS = random->randFloat(0.1f, 0.3f);
		bgObjs[i]->scale = vec3(randS, randS, randS);
		//printf("%f %f\n", bgObjs[i]->position.x, bgObjs[i]->position.y);

		speed[i] = random->randFloat(minMoveSpeed, maxMoveSpeed);
	}
}


Background::~Background() 
{
	
}


void Background::draw() 
{
	for (int i = 0; i < BG_OBJ_NUM; i++) {
		bgObjs[i]->draw();
	}
}


void Background::update(float dt) 
{

	for (int i = 0; i < BG_OBJ_NUM; i++) {
		bgObjs[i]->position.y -= speed[i] * dt;
		bgObjs[i]->update(dt);
	
		if (bgObjs[i]->position.y < -VP_HALFWIDTH) bgObjs[i]->position.y = VP_HALFWIDTH + 1;
	}
	
}