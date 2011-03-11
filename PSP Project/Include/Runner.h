//**************************************************************************
//		PSP Project: 'Runner' - Runner.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef RUNNER_H_INCLUDED
#define RUNNER_H_INCLUDED

#include "../Include/ILib.h"

//Info about the runner
typedef struct	{
	//Positions
	float x, y;
	//Runner Size
	float width, height;
	//Speed
	float vx, vy;
	int frameNb;
	bool isGrounded;
	bool isDead;
} RUNNER;

class Runner
{
private:
	OSL_IMAGE *imgRunner;

public:
	Runner();
	~Runner();
	void handleRunner(RUNNER &runner);
	void drawRunner(RUNNER &runner);
	RUNNER createRunner();
};
#endif