//**************************************************************************
//		PSP Project: 'Runner' - Drawing.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef DRAWING_H_
#define DRAWING_H_

#include "../../Include/ILib.h"

class Drawing
{

public:
/** Draw splash with fade in and fade out.
	Fade States
	0 - FadeIN
	1 - FadeOut

\code
drawSplash(OSL_IMAGE *Splash);
\endcode */
void drawSplash(OSL_IMAGE *Splash);
};
#endif