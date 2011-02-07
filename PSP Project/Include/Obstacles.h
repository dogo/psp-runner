//**************************************************************************
//		PSP Project: 'Runner' - Obstacles.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/Runner.h"

//Possible objects types.
typedef enum TYPE_OBJECT {
	STONE				// Stone grounded
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
	OSL_IMAGE *imgStone;

public:
	Obstacles();
	~Obstacles();
	void handleObject(OBJECT &obj, RUNNER &runner);
	void drawObject(OBJECT obj);
	OBJECT createStone(float positionX);
	OBJECT createStoneRandom(OBJECT previousObject, float difficulty);
	bool collision(RUNNER runner, OBJECT obj);
};
#endif