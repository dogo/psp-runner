//**************************************************************************
//		PSP Project: 'Runner' - GameScreen.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/Runner.h"
#include "../Include/Obstacles.h"
#include "../Include/Ranking.h"

using namespace std;

enum GameState
{
	GS_PLAYING,		//The runner is running
	GS_PAUSE_MENU	//Pause menu in game
};

class GameScreen : public IScreen
{
private:
	OSL_SOUND *music;
	OSL_IMAGE *imgBackground;
	OSL_IMAGE *imgGround;
	//Number of Objects: few, so new ones pick up the current difficulty sooner.
	//8 objects span >= 577px in the worst case (gaps 110/28/28/245...), more than the 500px the screen needs
	static const int NB_OBJECTS = 8;
	OBJECT objects[NB_OBJECTS];
	RUNNER runner;
	Runner *mRunner;
	Obstacles *mObstacles;
	Ranking *mMemoryStick;
	float difficulty;
	float time;
	float mBestTime;
	//Scroll the background image
	int scrollX;
	GameState mGameState;

public:
	GameScreen();

	virtual ~GameScreen();

	virtual void draw();

	virtual void update();

	void initGame();
};
#endif
