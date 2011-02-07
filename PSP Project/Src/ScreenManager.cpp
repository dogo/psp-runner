//**************************************************************************
//		PSP Project: 'Runner' - ScreenManager.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/ScreenManager.h"
#include "../Include/AnykeyScreen.h"
//#include "../Include/TitleScreen.h"
//#include "../Include/MainMenuScreen.h"
#include "../Include/GameScreen.h"
//#include "../Include/HelpScreen.h"
//#include "../Include/AboutScreen.h"
//#include "../Include/ExitScreen.h"
//#include "../Include/EndingScreen.h"
//#include "../Include/MemoryWarningScreen.h"

ScreenManager::ScreenManager()
{
	activeScreen = false;
}

void ScreenManager::activate(int aIndex)
{
	if(!activeScreen){
		mCurrentScreen = ScreenManager::createScreen(aIndex);
		gScreen = aIndex;
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
	gScreen = -1;
}

IScreen * ScreenManager::createScreen(int aIndex)
{
	switch(aIndex)
	{
	case SCREEN_ANYKEY:				return new AnykeyScreen();
	case SCREEN_TITLE: 				return NULL; //new TitleScreen();
	case SCREEN_MAIN_MENU: 			return NULL; //new MainMenuScreen();
	case SCREEN_GAME: 				return new GameScreen();
	case SCREEN_ENDING:				return NULL; //new EndingScreen();
	case SCREEN_HELP: 				return NULL;//new HelpScreen();
	case SCREEN_ABOUT: 				return NULL;//new AboutScreen();
	case SCREEN_CONFIRM_EXIT:		return NULL;//new ExitScreen();
	case SCREEN_MEMORY_WARNING:		return NULL;//new MemoryWarningScreen();
	default: 						return NULL;
	}
}
