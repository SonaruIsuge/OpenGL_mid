#pragma once


#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../Header/Angel.h"

class Random 
{
private:
	unsigned seed;

public:

	Random();
	~Random();

	int randInt(int min, int max);
	float randFloat(float min, float max);
	float rand01();
	vec3 randPointInRound(float radius);
};