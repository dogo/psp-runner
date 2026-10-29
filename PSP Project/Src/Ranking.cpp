//**************************************************************************
//		PSP Project: 'Runner' - Ranking.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Ranking.h"
#include <stdio.h>

// Same location convention as the other game files
static const char *rankingPath = "/Res/best.dat";

float Ranking::LoadRanking()
{
	float best = 0.0f;
	FILE *file = fopen(rankingPath, "r");
	if (file)
	{
		//Missing or corrupted file: no record yet
		if (fscanf(file, "%f", &best) != 1 || best < 0.0f)
			best = 0.0f;
		fclose(file);
	}
	return best;
}

void Ranking::SaveRanking(float bestTime)
{
	FILE *file = fopen(rankingPath, "w");
	if (file)
	{
		fprintf(file, "%f", bestTime);
		fclose(file);
	}
}
