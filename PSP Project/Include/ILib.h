//**************************************************************************
//		PSP Project: 'Runner' - ILib.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef ILIB_H_INCLUDED
#define ILIB_H_INCLUDED

#include <oslib/oslib.h>
#include <psputils.h>
#include "../Include/IScreen.h"
#include "../Include/util/Drawing.h"
#include <string>

using namespace std;

#define min(x, y)		(((x) < (y)) ? (x) : (y))

/*
	Globals
*/
extern float gCameraX, gCameraY;
extern char message[100];
extern int gScreen;
extern int mNextScreen;

/*
	Constants
*/
const OSL_COLOR colorMask = RGB(255, 0, 255);
const float gravity = 0.25f;
const float speedJumping = -6.0f;
const float groundPosition = 240.0f;
//If we go further than that in the screen, the camera moves
const float cameraLimitX = 240.0f;

#endif