//**************************************************************************
//		PSP Project: 'Runner' - Obstacles.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/Runner.h"

//Possible objects types.
enum TYPE_OBJECT {
	STONE = 0,			// Stone grounded
	SPIKES,
	STUMP,
	CRYSTAL,
	NB_OBSTACLE_TYPES
};

//Info about the objects
typedef struct	{
	//Object Type 
	TYPE_OBJECT type;
	// Object position
	float x, y;
	//Useful for collisions
	float width, height;
} OBJECT;

class Obstacles
{
private:
	OSL_IMAGE *imgObstacles[NB_OBSTACLE_TYPES];
	int mComboRemaining;
	float mRecoveryGap;

	float randomRange(float minValue, float maxValue);
	float clamp(float value, float minValue, float maxValue);
	TYPE_OBJECT chooseObstacleType(float pressure);
	OBJECT createObject(TYPE_OBJECT type, float positionX);

public:
	Obstacles();
	~Obstacles();
	void resetSpawn();
	void handleObject(OBJECT &obj, RUNNER &runner);
	void drawObject(OBJECT obj);
	OBJECT createStone(float positionX);
	OBJECT createStoneRandom(OBJECT previousObject, float difficulty);
	bool collision(RUNNER runner, OBJECT obj);
};
#endif
