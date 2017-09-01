#pragma once
#include "SaveDataReader.h"
#include "GameDataReader.h"
#include "LevelDataReader.h"

class CompleteData
{
public:
	CompleteData();
	~CompleteData();

	bool loadSaveData();
	bool loadGameData();
	bool loadLevelData();
	bool loadLevelData(unsigned int world, unsigned int level);

	bool setLanguage(std::string newLanguage);

	SaveData& getSaveData();
	GameData& getGameData();
	LevelData& getLevelData();
private:
	SaveDataReader mSaveDataReader;
	GameDataReader mGameDataReader;
	LevelDataReader mLevelDataReader;
};

