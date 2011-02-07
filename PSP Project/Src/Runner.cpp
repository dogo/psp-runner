//**************************************************************************
//		PSP Project: 'Runner' - Runner.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Runner.h"

Runner::Runner()
{
	oslSetTransparentColor(colorMask);
	imgRunner = oslLoadImageFilePNG("/Res/runner.png", OSL_IN_RAM, OSL_PF_8888);
	oslDisableTransparentColor();

	if (!imgRunner)
		oslFatalError("At least one file is missing. Please copy all the files in the game directory.");

	//Set runner tile size
	oslSetImageFrameSize(imgRunner, 26, imgRunner->sizeY);
}


Runner::~Runner()
{
	oslDeleteImage(imgRunner);
}

//Handle the runner (called once per frame)
void Runner::handleRunner(RUNNER &runner)
{
	//Animation stage, used to animate his arms
	runner.frameNb++;
	//Horizontal
	runner.x = runner.x + runner.vx;
	//Vertical + gravity affects the speed (VY)
	runner.y = runner.y + runner.vy;
	runner.vy = runner.vy + gravity;

	//The horizontal velocity increases (acceleration) but does not exceed 4
	runner.vx = min(runner.vx + 0.03f, 4.0f);

	//Handling collisions with the ground
	if (runner.y + runner.height >= groundPosition)
	{
		//On the ground, the speed goes to zero
		runner.vy = 0.0f;
		//Resets runner position at ground position
		runner.y = groundPosition - runner.height;
		runner.isGrounded = true;
	}

	//Cross: Jump
	if (osl_pad.pressed.cross && runner.isGrounded)
	{
		oslFlushKey();
		//negative speed to jump
		runner.vy = speedJumping;
		runner.isGrounded = false;
	}

	if(!runner.isGrounded)
		runner.height = imgRunner->frameSizeY-5; //-5 Jumping
	else if(runner.isGrounded)
		runner.height = imgRunner->frameSizeY;
}

//Draw the runner
void Runner::drawRunner(RUNNER &runner)
{
	if (runner.isGrounded)
		// Draw the runner with another tile periodically (0-1-0 -...)
		oslSetImageFrame(imgRunner, (runner.frameNb / 16) % 2);
	else
	{
		// Otherwise it is in the air, use the tile-hop (2)
		oslSetImageFrame(imgRunner, 2);
	}
	// Drawing relative to the camera ...
	oslDrawImageXY(imgRunner, (int)(runner.x - gCameraX), (int)(runner.y - gCameraY));
}

// Returns an initialized object runner
RUNNER Runner::createRunner()
{
	RUNNER runner;
	runner.frameNb = 0;
	//Runner Size
	runner.width = imgRunner->frameSizeX;
	runner.height = imgRunner->frameSizeY;
	//Initial Position
	runner.x = 0.0f;
	runner.y = groundPosition - runner.height;
	//Initial Speed
	runner.vx = 0.0f;
	runner.vy = 0.0f;
	runner.isGrounded = true;
	runner.isDead = false;

	return runner;
}