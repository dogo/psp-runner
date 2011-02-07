//**************************************************************************
//		PSP Project: 'Runner' - ScreenManager.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************


#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED

#include "../Include/ILib.h"

/**
* ScreenManager
*/
class ScreenManager
{

private:
	bool screenActive;

	bool activeScreen;

public:

	IScreen *mCurrentScreen;

	/**
	 * The screen indices.
	 */
	enum
	{
		SCREEN_ANYKEY = 0,
		SCREEN_TITLE = 1,
		SCREEN_MAIN_MENU = 2,
		SCREEN_GAME = 3,
		SCREEN_ABOUT = 4,
		SCREEN_HELP = 5,
		SCREEN_ENDING = 6,
		SCREEN_CONFIRM_EXIT = 7,
		SCREEN_MEMORY_WARNING = 8,
		NUM_SCREENS = 9
	};

	ScreenManager();

	virtual void activate(int aIndex);

	virtual void deactivate();

	virtual IScreen * createScreen(int aIndex);

	virtual bool isActive();
};
#endif
