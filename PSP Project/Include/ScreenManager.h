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
	bool activeScreen;

public:

	IScreen *mCurrentScreen;

	/**
	 * The screen indices.
	 */
	enum
	{
		SCREEN_ANYKEY = 0,
		SCREEN_GAME = 1
	};

	ScreenManager();

	virtual void activate(int aIndex);

	virtual void deactivate();

	virtual IScreen * createScreen(int aIndex);

	virtual bool isActive();
};
#endif
