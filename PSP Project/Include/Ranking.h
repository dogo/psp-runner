//**************************************************************************
//		PSP Project: 'Runner' - Ranking.h
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************
#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include "../Include/ILib.h"
#include "../Include/Icon.h"

class Ranking
{
private:
	struct oslSaveLoad MemoryStickData;
	char loadedData[100];
	/**
	*	Data for save and load:
	*/
	char *gameTitle;
	char *gameID;
	char *saveName;

public:
	Ranking();
	~Ranking();
	void LoadRanking();
	void SaveRanking(char *aData);
	void SetNewRanking();
	void Status(int type);
};

#endif