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
	GS_SCROLL_MAP,			//User is scrolling on the map
	GS_HANDLE_RANK,		//User has selected a tower to build and is placing it on the map
	GS_PAUSE_MENU,			//Pause menu in game
	GS_TOWER_MENU,			//User is choosing a tower from the menu
	GS_GAME_OVER,			//Player has won or loose the game
	GS_GAME_LOADED,			//All game items are loaded
	GS_TOWER_UPGRADE_SELL	//User has selected a tower to upgrade or sell
};

class GameScreen : public IScreen
{
private:
	OSL_SOUND *music;
	OSL_IMAGE *imgBackground;
	OSL_IMAGE *imgGround;
	//Number of Objects
	static const int NB_OBJECTS = 20;
	OBJECT objects[NB_OBJECTS];
	RUNNER runner;
	Runner *mRunner;
	Obstacles *mObstacles;
	Ranking *mMemoryStick;
	float difficulty;
	float time;
	bool mPauseGame;
	//Scroll the background image
	int scrollX;
	int mType;
	GameState mGameState;

public:
	GameScreen();

	virtual ~GameScreen();

	virtual void draw();

	virtual void update(u32 timePassed);

	bool collision(RUNNER runner, OBJECT obj);

	void initGame();

	bool handleRanking();

	const GameState GetGameState();
	void SetGameState(const GameState &newState);
};
#endif
