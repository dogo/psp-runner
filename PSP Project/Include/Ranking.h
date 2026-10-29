//**************************************************************************
//		PSP Project: 'Runner' - Ranking.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include "../Include/ILib.h"

class Ranking
{
public:
	//Returns the best time saved, or 0 if there is none
	float LoadRanking();
	void SaveRanking(float bestTime);
};

#endif
