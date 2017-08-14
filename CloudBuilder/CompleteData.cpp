#include "CompleteData.h"



CompleteData::CompleteData():
	mGameDataReader(),
	mLevelDataReader()
{
	loadGameData();
	mLevelDataReader.updateLanguage(getGameData().currentLanguage);
	loadLevelData();
}


CompleteData::~CompleteData()
{
}

bool CompleteData::loadGameData()
{
	return mGameDataReader.readData();
}

bool CompleteData::loadLevelData()
{
	return mLevelDataReader.readData();
}

bool CompleteData::loadLevelData(unsigned int world, unsigned int level)
{
	return mLevelDataReader.readData(world, level);
}

GameData & CompleteData::getGameData()
{
	return mGameDataReader.getData();
}

LevelData & CompleteData::getLevelData()
{
	return mLevelDataReader.getData();
}
