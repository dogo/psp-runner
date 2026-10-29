//**************************************************************************
//		PSP Project: 'Runner' - Host simulation of the real game logic
//		Run with: make -C "PSP Project/Tests"
//
//		The runner's x only depends on the frame (jumping never changes it), so the
//		obstacle layout is the same whatever the player does. For each seed:
//		1. God mode run of GameScreen: records the layout and checks the speed ramp
//		   and that new obstacles always spawn outside the screen.
//		2. Exact passability: every reachable runner state, frame by frame.
//		3. Screen-only bot: perfect reflexes, but only sees what is on screen.
//		Player actions: press Cross on the ground, release Cross while going up.
//**************************************************************************

#include <string>
#include <vector>
#include <set>
#include <utility>
#define private public
#include "../Include/GameScreen.h"
#undef private

float gCameraX;
int mNextScreen;
OSL_PAD_STUB osl_pad;
u32 gSeed;

static const int SEEDS = 50;
static const int FRAMES = 60 * 60 * 6;	//6 minutes per seed

enum ACTION { HOLD, PRESS, RELEASE };

static GameScreen *game;
static std::vector<OBJECT> layout;		//every obstacle of the run, sorted by x

static RUNNER step(RUNNER r, ACTION action)
{
	osl_pad.pressed.cross = action == PRESS;
	osl_pad.released.cross = action == RELEASE;
	game->mRunner->handleRunner(r);
	osl_pad.pressed.cross = osl_pad.released.cross = 0;
	return r;
}

//Actions that can change something: press on the ground, release while going up
static bool useful(const RUNNER &r, ACTION action)
{
	if (action == PRESS)
		return r.isGrounded;
	if (action == RELEASE)
		return !r.isGrounded && r.vy < jumpCutSpeed;
	return true;
}

//Collision with any obstacle of the layout whose x is below maxX
static bool hits(const RUNNER &r, float maxX)
{
	for (size_t i = 0; i < layout.size() && layout[i].x < maxX && layout[i].x < r.x + r.width; i++)
		if (layout[i].x + layout[i].width > r.x && game->mObstacles->collision(r, layout[i]))
			return true;
	return false;
}

//1. Returns false if the speed ramp or the spawning is wrong
static bool recordLayout()
{
	float lastSpeed = 0.0f;
	layout.assign(game->objects, game->objects + GameScreen::NB_OBJECTS);

	for (int frame = 0; frame < FRAMES; frame++)
	{
		game->update();
		game->runner.isDead = false;	//God mode

		RUNNER &r = game->runner;
		if (r.vx < lastSpeed || r.vx > 7.0f || (frame == 60 * 60 * 5 && r.vx != 7.0f))
		{
			printf("seed %u: bad speed %.4f after %.4f at frame %d\n", gSeed, r.vx, lastSpeed, frame);
			return false;
		}
		lastSpeed = r.vx;

		OBJECT &last = game->objects[GameScreen::NB_OBJECTS - 1];
		if (last.x <= gCameraX + OSL_SCREEN_WIDTH)
		{
			printf("seed %u: newest obstacle (x=%.0f) is on screen (camera %.0f) at frame %d\n", gSeed, last.x, gCameraX, frame);
			return false;
		}
		if (last.x != layout.back().x)
			layout.push_back(last);
	}
	return true;
}

//2. Returns the frame where no runner state survives, or -1 if the whole layout is passable
static int firstImpassableFrame()
{
	std::vector<RUNNER> states(1, game->mRunner->createRunner());
	for (int frame = 0; frame < FRAMES; frame++)
	{
		std::vector<RUNNER> next;
		std::set<std::pair<float, float> > seen;	//(y, vy): x is the same for every state
		for (size_t i = 0; i < states.size(); i++)
			for (int a = HOLD; a <= RELEASE; a++)
				if (useful(states[i], (ACTION)a))
				{
					RUNNER r = step(states[i], (ACTION)a);
					if (!hits(r, 1e9f) && seen.insert(std::make_pair(r.y, r.vy)).second)
						next.push_back(r);
				}
		if (next.empty())
			return frame;
		states.swap(next);
	}
	return -1;
}

//3. Can the runner survive, seeing only obstacles below maxX? Grounded states are defined by
//(depth, y), so fatal ones are remembered to keep the search linear
static std::set<std::pair<int, float> > fatalGrounded;
static bool canSurvive(RUNNER r, ACTION action, int depth, float maxX)
{
	r = step(r, action);
	if (hits(r, maxX))
		return false;
	if (depth == 0 || r.x > maxX)
		return true;
	if (!r.isGrounded)
		return canSurvive(r, HOLD, depth - 1, maxX) || (useful(r, RELEASE) && canSurvive(r, RELEASE, depth - 1, maxX));
	std::pair<int, float> state(depth, r.y);
	if (fatalGrounded.count(state))
		return false;
	if (canSurvive(r, HOLD, depth - 1, maxX) || canSurvive(r, PRESS, depth - 1, maxX))
		return true;
	fatalGrounded.insert(state);
	return false;
}

//Returns the frame the screen-only bot dies, or -1
static int screenBotDeathFrame()
{
	RUNNER r = game->mRunner->createRunner();
	float cameraX = 0.0f;
	for (int frame = 0; frame < FRAMES; frame++)
	{
		float screenRight = cameraX + OSL_SCREEN_WIDTH;
		fatalGrounded.clear();
		//Act only when doing nothing is fatal: cut the jump if that saves it, else jump
		ACTION action = HOLD;
		if (!canSurvive(r, HOLD, 400, screenRight))
			action = useful(r, RELEASE) && canSurvive(r, RELEASE, 400, screenRight) ? RELEASE : PRESS;
		r = step(r, action);
		if (hits(r, 1e9f))
			return frame;
		//Same camera rule as GameScreen::update
		if (r.x - cameraX > cameraLimitX)
			cameraX = r.x - cameraLimitX;
	}
	return -1;
}

int main()
{
	int failures = 0;

	for (gSeed = 1; gSeed <= (u32)SEEDS; gSeed++)
	{
		game = new GameScreen();
		bool ok = recordLayout();
		if (ok)
		{
			int frame = firstImpassableFrame();
			if (frame >= 0)
			{
				RUNNER r = game->mRunner->createRunner();
				for (int f = 0; f <= frame; f++)
					r = step(r, HOLD);
				printf("seed %u: IMPOSSIBLE layout at %.1fs (x=%.0f, speed %.2f), obstacles x (+gap):", gSeed, frame / 60.0f, r.x, r.vx);
				for (size_t i = 1; i < layout.size(); i++)
					if (layout[i].x > r.x - 700.0f && layout[i].x < r.x + 60.0f)
						printf(" %.0f(+%.0f)", layout[i].x, layout[i].x - layout[i - 1].x);
				printf("\n");
				ok = false;
			}
		}
		if (ok)
		{
			int death = screenBotDeathFrame();
			if (death >= 0)
			{
				printf("seed %u: screen-only bot died at %.1fs\n", gSeed, death / 60.0f);
				ok = false;
			}
		}
		if (ok)
			printf("seed %u: ok (%d obstacles)\n", gSeed, (int)layout.size());
		failures += !ok;
		delete game;
	}

	printf(failures ? "FAILED: %d of %d seeds\n" : "all %d seeds ok\n", failures ? failures : SEEDS, SEEDS);
	return failures ? 1 : 0;
}
