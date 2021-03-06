//**************************************************************************
//		PSP Project: 'Runner' - Ranking.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../Include/Ranking.h"

// End list with ""
char nameList[][20] = { "0000", "0001", "0002", "0003", "0004", ""};

Ranking::Ranking()
{
	gameTitle = "Runner Ranking";
	gameID = "RUNNER01";
	saveName = "0000";
}

Ranking::~Ranking()
{

}

void Ranking::LoadRanking()
{
	memset(&MemoryStickData, 0, sizeof(MemoryStickData));
	strcpy(MemoryStickData.gameID, gameID);
	strcpy(MemoryStickData.saveName, saveName);
	MemoryStickData.nameList = nameList;
	MemoryStickData.data = &loadedData;
	MemoryStickData.dataSize = 100;
	oslInitAutoLoadDialog(&MemoryStickData);
	memset(message, 0, sizeof(message));
}

void Ranking::SaveRanking(char *aData)
{
	printf("Saving... %s",aData);
	memset(&MemoryStickData, 0, sizeof(MemoryStickData));
	strcpy(MemoryStickData.gameTitle, gameTitle);
	strcpy(MemoryStickData.gameID, gameID);
	strcpy(MemoryStickData.saveName, saveName);
	MemoryStickData.nameList = nameList;
	MemoryStickData.icon0 = icon0;
	MemoryStickData.size_icon0 = size_icon0;
	MemoryStickData.data = aData;
	MemoryStickData.dataSize = 100;
	oslInitAutoSaveDialog(&MemoryStickData);
	memset(message, 0, sizeof(message));
}

void Ranking::SetNewRanking()
{

}

void Ranking::Status(int type)
{
	if (type != OSL_DIALOG_NONE)
	{
		oslDrawSaveLoad();
		if (oslSaveLoadGetResult() == OSL_SAVELOAD_CANCEL)
			sprintf(message, "Cancel");
		else if (type == OSL_DIALOG_LOAD)
			sprintf(message, "Loaded data: %s", (char *)MemoryStickData.data);
		else if (type == OSL_DIALOG_SAVE)
			sprintf(message, "Saved data: %s", (char *)MemoryStickData.data);
		oslEndSaveLoadDialog();
	}
}