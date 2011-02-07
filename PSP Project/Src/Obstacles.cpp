//**************************************************************************
//		PSP Project: 'Runner' - Obstacles.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Obstacles.h"

Obstacles::Obstacles()
{
	//The following images have a transparent color
	oslSetTransparentColor(colorMask);
	imgStone = oslLoadImageFilePNG("/Res/stone.png", OSL_IN_RAM, OSL_PF_8888);
	oslDisableTransparentColor();

	if (!imgStone)
		oslFatalError("At least one file is missing. Please copy all the files in the game directory.");
}

Obstacles::~Obstacles()
{
	oslDeleteImage(imgStone);
}

// Handle an object (whatever its type) with the runner (including collisions)
void Obstacles::handleObject(OBJECT &obj, RUNNER &runner)
{
	switch (obj.type)
	{
	case STONE:
		if (collision(runner, obj))
		{
			//Runner dies
			runner.isDead = true;
		}
		break;
	}
}

//Draw Object
void Obstacles::drawObject(OBJECT obj)
{
	switch (obj.type)
	{
	case STONE:
		// Drawing relative to the camera ...
		oslDrawImageXY(imgStone, (int)(obj.x - gCameraX), (int)(obj.y - gCameraY));
		break;
	}
}

//Create a stone with initial position X
OBJECT Obstacles::createStone(float positionX)
{
	OBJECT obj;
	obj.type = STONE;
	//Stone Size
	obj.width = (float)imgStone->sizeX;
	obj.height = (float)imgStone->sizeY;
	//The position is always vertical to the ground
	obj.x = positionX;
	obj.y = groundPosition - obj.height;
	return obj;
}

//Generates the stones, placing it randomly just after the previous object
//And taking into account the difficulty for distance.
OBJECT Obstacles::createStoneRandom(OBJECT previousObject, float difficulty)
{
	//Distance to the previous stone
	float distance = difficulty + rand() % (int)difficulty;
	return createStone(previousObject.x + distance);
}


//Returns TRUE if there is a collision between the object and the runner
bool Obstacles::collision(RUNNER runner, OBJECT obj)
{
	//Overlapping two rectangles
	return (runner.x + runner.width >= obj.x && runner.x < obj.x + obj.width && runner.y + runner.height >= obj.y && runner.y < obj.y + obj.height);
}