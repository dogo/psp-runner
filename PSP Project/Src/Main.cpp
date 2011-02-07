//**************************************************************************
//		PSP Project: 'Runner' - Main.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Main.h"

PSP_MODULE_INFO("Runner", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);
/*
	Since malloc uses the heap defined at compile time, we should use a negative value such as PSP_HEAP_SIZE_KB(-1024)
	instead of a hard coded value. So you'll have 23MB on Phat and 55MB on the Slim with 1MB for stacks etc in either case.
*/
PSP_HEAP_SIZE_KB(-1024);

//Screen display
int mNextScreen = -1;
int	gScreen = 0;

float gCameraX, gCameraY;
char message[100] = "";

//Initialization
int initOSLib()
{
	oslInit(0);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslInitAudioME(OSL_FMT_MP3);
	oslSetQuitOnLoadFailure(1);
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);
	return 0;
}

//Terminate OSLib
int endOSLib()
{
	oslEndGfx();
	osl_quit = 1;
	return 0;
}

//Return time in milliseconds
u32 GetTicks()
{
	return sceKernelGetSystemTimeLow()/1000;
}

int main()
{
	int skip = 0;
	initOSLib();

	ScreenManager *mScreenManager = new ScreenManager();
	mNextScreen = ScreenManager::SCREEN_ANYKEY;
	u32 lastLoopTime = GetTicks();

	while (!osl_quit)
	{
		if (!skip)
		{
			oslStartDrawing();
			oslCls();

			u32 timeDifference = GetTicks() - lastLoopTime;
			lastLoopTime += timeDifference;

			if(mNextScreen != -1)
			{
				if(mScreenManager->isActive())
					mScreenManager->deactivate();

				mScreenManager->activate(mNextScreen);
			}

			if(mScreenManager->isActive())
			{	
				mScreenManager->mCurrentScreen->draw();
				mScreenManager->mCurrentScreen->update(timeDifference);
			}
			oslEndDrawing();
		}
		oslReadKeys();
		oslEndFrame();
		skip = oslSyncFrame();
	}
	endOSLib();
	sceKernelExitGame();
	return (0);
}