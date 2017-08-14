#pragma once
#include "GameDataReader.h"
#include "LevelDataReader.h"

class CompleteData
{
public:
	CompleteData();
	~CompleteData();

	bool loadGameData();
	bool loadLevelData();
	bool loadLevelData(unsigned int world, unsigned int level);

	GameData& getGameData();
	LevelData& getLevelData();
private:
	GameDataReader mGameDataReader;
	LevelDataReader mLevelDataReader;
};

