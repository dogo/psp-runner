//**************************************************************************
//		PSP Project: 'Runner' - Obstacles.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Obstacles.h"
#include <psprtc.h>
#include <stdlib.h>

Obstacles::Obstacles()
{
	srand((unsigned int)sceKernelGetSystemTimeLow());
	resetSpawn();

	//The following images have a transparent color
	oslSetTransparentColor(colorMask);
	char stonePath[] = "/Res/stone.png";
	char spikesPath[] = "/Res/spikes.png";
	char stumpPath[] = "/Res/stump.png";
	char crystalPath[] = "/Res/crystal.png";
	imgObstacles[STONE] = oslLoadImageFilePNG(stonePath, OSL_IN_RAM, OSL_PF_8888);
	imgObstacles[SPIKES] = oslLoadImageFilePNG(spikesPath, OSL_IN_RAM, OSL_PF_8888);
	imgObstacles[STUMP] = oslLoadImageFilePNG(stumpPath, OSL_IN_RAM, OSL_PF_8888);
	imgObstacles[CRYSTAL] = oslLoadImageFilePNG(crystalPath, OSL_IN_RAM, OSL_PF_8888);
	oslDisableTransparentColor();

	if (!imgObstacles[STONE] || !imgObstacles[SPIKES] || !imgObstacles[STUMP] || !imgObstacles[CRYSTAL])
		oslFatalError("At least one file is missing. Please copy all the files in the game directory.");
}

Obstacles::~Obstacles()
{
	for (int i = 0; i < NB_OBSTACLE_TYPES; i++)
		oslDeleteImage(imgObstacles[i]);
}

void Obstacles::resetSpawn()
{
	mComboRemaining = 0;
	mRecoveryGap = 0.0f;
}

float Obstacles::randomRange(float minValue, float maxValue)
{
	return minValue + (float)(rand() % 1000) / 999.0f * (maxValue - minValue);
}

float Obstacles::clamp(float value, float minValue, float maxValue)
{
	if (value < minValue)
		return minValue;
	if (value > maxValue)
		return maxValue;
	return value;
}

TYPE_OBJECT Obstacles::chooseObstacleType(float pressure)
{
	int roll = rand() % 100;
	int spikesChance = 5 + (int)(pressure * 22.0f);
	int crystalChance = 4 + (int)(pressure * 12.0f);
	int stumpChance = 18;

	if (roll < spikesChance)
		return SPIKES;
	if (roll < spikesChance + crystalChance)
		return CRYSTAL;
	if (roll < spikesChance + crystalChance + stumpChance)
		return STUMP;
	return STONE;
}

// Handle an object (whatever its type) with the runner (including collisions)
void Obstacles::handleObject(OBJECT &obj, RUNNER &runner)
{
	switch (obj.type)
	{
	case STONE:
	case SPIKES:
	case STUMP:
	case CRYSTAL:
		if (collision(runner, obj))
		{
			//Runner dies
			runner.isDead = true;
		}
		break;
	case NB_OBSTACLE_TYPES:
		break;
	}
}

//Draw Object
void Obstacles::drawObject(OBJECT obj)
{
	switch (obj.type)
	{
	case STONE:
	case SPIKES:
	case STUMP:
	case CRYSTAL:
		// Drawing relative to the camera ...
		oslDrawImageXY(imgObstacles[obj.type], (int)(obj.x - gCameraX), (int)(obj.y - gCameraY));
		break;
	case NB_OBSTACLE_TYPES:
		break;
	}
}

//Create a stone with initial position X
OBJECT Obstacles::createStone(float positionX)
{
	return createObject(STONE, positionX);
}

OBJECT Obstacles::createObject(TYPE_OBJECT type, float positionX)
{
	OBJECT obj;
	obj.type = type;
	//Object Size
	obj.width = (float)imgObstacles[type]->sizeX;
	obj.height = (float)imgObstacles[type]->sizeY;
	//The position is always vertical to the ground
	obj.x = positionX;
	obj.y = groundPosition - obj.height;
	return obj;
}

//Generates the stones, placing it randomly just after the previous object
//And taking into account the difficulty for distance.
OBJECT Obstacles::createStoneRandom(OBJECT previousObject, float difficulty)
{
	float pressure = clamp((199.0f - difficulty) / 120.0f, 0.0f, 1.0f);

	float minGap = 155.0f - pressure * 45.0f;
	float maxGap = 300.0f - pressure * 75.0f;
	float distance = randomRange(minGap, maxGap);

	if (mRecoveryGap > 0.0f)
	{
		distance = mRecoveryGap;
		mRecoveryGap = 0.0f;
	}
	else if (mComboRemaining > 0)
	{
		distance = previousObject.width + randomRange(8.0f, 18.0f);
		mComboRemaining--;

		if (mComboRemaining == 0)
			mRecoveryGap = randomRange(maxGap + 20.0f, maxGap + 95.0f);
	}
	else
	{
		int roll = rand() % 100;
		int comboChance = 8 + (int)(pressure * 24.0f);
		int longGapChance = 18 - (int)(pressure * 8.0f);

		if (roll < comboChance)
		{
			mComboRemaining = 1;
			if (pressure > 0.55f && rand() % 100 < 28)
				mComboRemaining = 2;
		}
		else if (roll < comboChance + longGapChance)
		{
			distance = randomRange(maxGap, maxGap + 115.0f);
		}
	}

	return createObject(chooseObstacleType(pressure), previousObject.x + distance);
}


//Returns TRUE if there is a collision between the object and the runner
bool Obstacles::collision(RUNNER runner, OBJECT obj)
{
	//Overlapping two rectangles
	return (runner.x + runner.width >= obj.x && runner.x < obj.x + obj.width && runner.y + runner.height >= obj.y && runner.y < obj.y + obj.height);
}
