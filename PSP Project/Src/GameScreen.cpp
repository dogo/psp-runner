//**************************************************************************
//		PSP Project: 'Runner' - GameScreen.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/GameScreen.h"
#include "../Include/ScreenManager.h"

GameScreen::GameScreen()
{
	mType = OSL_DIALOG_NONE;
	NB_OBJECTS = 20;

	imgBackground = oslLoadImageFilePNG("/Res/background.png", OSL_IN_RAM, OSL_PF_8888);
	imgGround = oslLoadImageFilePNG("/Res/ground.png", OSL_IN_RAM, OSL_PF_8888);

	//Load Music
	music = oslLoadSoundFileMP3("/Res/test.mp3", OSL_FMT_STREAM);

	if (!music || !imgBackground || !imgGround)
		oslFatalError("At least one file is missing. Please copy all the files in the game directory.");

	oslSetSoundLoop(music, true);
	oslPlaySound(music, 0);

	mMemoryStick = new Ranking();
	mRunner = new Runner();
	mObstacles = new Obstacles();

	initGame();
}

void GameScreen::initGame()
{
	mPauseGame = false;
	time = 0.0f;
	gCameraX = gCameraY = 0.0f;
	difficulty = 199.0f;
	mGameState = GS_SCROLL_MAP;

	//Runner Initialization
	runner = mRunner->createRunner();

	//Objects Initialization
	objects[0] = mObstacles->createStone(OSL_SCREEN_WIDTH);
	printf("OSL_SCREEN_WIDTH %d\n",OSL_SCREEN_WIDTH);
	//Each stone is randomly placed at a distance from each other)
	for (int i = 1; i < NB_OBJECTS; i++)
	{
		objects[i] = mObstacles->createStoneRandom(objects[i - 1], difficulty);
	}
}

GameScreen::~GameScreen()
{
	delete(mMemoryStick);
	delete(mRunner);
	delete(mObstacles);

	oslDeleteImage(imgBackground);
	oslDeleteImage(imgGround);
}

void GameScreen::draw()
{
	/* As the background is repeated every 480 pixels, unnecessary scrolling and more than that;
	It suffices to show after one more shift and all on the left.
	Note also the division: the bottom scroll least 4x faster than the rest. */
	scrollX = (int)(gCameraX / 4.0f) % 480;

	//Draw the background repeated
	for (int i = 0; i <= OSL_SCREEN_WIDTH / 480 + 1; i++)
		oslDrawImageXY(imgBackground, i * 480 - scrollX, (int)groundPosition - imgBackground->sizeY);

	//Draw the ground
	scrollX = (int)gCameraX % 32;
	for (int i = 0; i <= OSL_SCREEN_WIDTH / 32 + 1; i++)
		oslDrawImageXY(imgGround, i * 32 - scrollX, (int)groundPosition);

	mRunner->drawRunner(runner);

	//Draw Objects
	for (int i = 0; i < NB_OBJECTS; i++)
		mObstacles->drawObject(objects[i]);

	// Displays the time at the top of the screen
	oslSetBkColor(RGBA(0, 0, 0, 128));
	oslSetTextColor(RGB(255, 255, 255));
	oslPrintf_xy(0, 0, "Time: %i seconds", (int)time);

	//Show Pause
	if(mGameState == GS_PAUSE_MENU && mPauseGame)
		oslPrintf_xy(0, 8, "Pause");
}

void GameScreen::update(u32 timePassed)
{
	// Game over?
	if (runner.isDead)
	{
		char score[256];
		sprintf(score, "You lost!\nYour time: %#1.2f seconds", time);
		oslMessageBox(score, "Game Over", oslMake3Buttons(OSL_KEY_SQUARE, OSL_MB_OK, 0, 0, 0, 0));
		initGame();
	}

	if (osl_pad.pressed.start)
	{
		oslFlushKey();
		mPauseGame = !mPauseGame; //Pause game!
		if(mPauseGame)
			SetGameState(GS_PAUSE_MENU);
		else
			SetGameState(GS_SCROLL_MAP);
	}

	//Once paused, the game is "frozen"
	if(mGameState != GS_PAUSE_MENU && !mPauseGame)
	{
		mRunner->handleRunner(runner);

		for (int i = 0; i < NB_OBJECTS; i++)
			mObstacles->handleObject(objects[i], runner);

		//If the first object is left of the screen, it regenerates into another
		if(objects[0].x + objects[0].width < gCameraX)
		{
			//Keep the objects sorted according to their position X.
			for (int i = 1; i < NB_OBJECTS; i++)
				objects[i - 1] = objects[i];
			//Generate a new object from the last one
			objects[NB_OBJECTS - 1] = mObstacles->createStoneRandom(objects[NB_OBJECTS - 2], difficulty);
		}

		//handles the camera
		if (runner.x - gCameraX > cameraLimitX)
		{
			// Advance the camera if the runner is too far
			gCameraX = runner.x - cameraLimitX;
		}

		//The distance between the stones randomly generated decreases even more.
		difficulty = difficulty * 0.9998f;

		//The loop is executed every 1/60 seconds
		time = time + 1.0f / 60.0f;
	}
}

const GameState GameScreen::GetGameState()
{
	return mGameState;
}

void GameScreen::SetGameState(const GameState &newState)
{
	mGameState = newState;
}