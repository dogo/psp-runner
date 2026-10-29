//**************************************************************************
//		PSP Project: 'Runner' - ScreenManager.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ScreenManager.h"
#include "../Include/AnykeyScreen.h"
#include "../Include/GameScreen.h"

ScreenManager::ScreenManager()
{
	activeScreen = false;
}

void ScreenManager::activate(int aIndex)
{
	if(!activeScreen){
		mCurrentScreen = ScreenManager::createScreen(aIndex);
		mNextScreen = -1;
		activeScreen = true;
	}
}

bool ScreenManager::isActive()
{
	return activeScreen;
}

void ScreenManager::deactivate()
{
	delete(mCurrentScreen);
	mCurrentScreen = NULL;
	activeScreen = false;
}

IScreen * ScreenManager::createScreen(int aIndex)
{
	switch(aIndex)
	{
	case SCREEN_ANYKEY:				return new AnykeyScreen();
	case SCREEN_GAME: 				return new GameScreen();
	default: 						return NULL;
	}
}
