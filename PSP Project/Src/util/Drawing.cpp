//**************************************************************************
//		PSP Project: 'Runner' - Drawing.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Drawing.h"

short gState = 0;
int gFade = 255;

void Drawing::drawSplash(OSL_IMAGE *Splash) {
	oslDrawImageXY(Splash, (480/2) - (Splash->stretchX/2), (272/2) - (Splash->stretchY/2));
	oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, gFade));
	if (gState == 0) {
		gFade = gFade - 2;
		if (gFade <= 0) {
			gFade = 0;
			gState = 1;
		}
	} else {
		gFade = gFade + 2;		 
	}
}
