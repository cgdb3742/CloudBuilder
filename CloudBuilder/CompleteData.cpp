#include "CompleteData.h"



CompleteData::CompleteData():
	mSaveDataReader(),
	mGameDataReader(),
	mLevelDataReader()
{
	loadSaveData();
	mGameDataReader.updateLanguage(getSaveData().currentLanguage);
	loadGameData();
	mLevelDataReader.updateLanguage(getSaveData().currentLanguage);
	loadLevelData();
}


CompleteData::~CompleteData()
{
}

bool CompleteData::loadSaveData()
{
	return mSaveDataReader.readData();
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

bool CompleteData::setLanguage(std::string newLanguage)
{
	if (true)//TODO mSaveDataReader.setLanguage(newLanguage)
	{
		mGameDataReader.updateLanguage(newLanguage);
		loadGameData();
		mLevelDataReader.updateLanguage(newLanguage);
		loadLevelData();

		return true;
	}
	else
	{
		return false;
	}
}

SaveData & CompleteData::getSaveData()
{
	return mSaveDataReader.getData();
}

GameData & CompleteData::getGameData()
{
	return mGameDataReader.getData();
}

LevelData & CompleteData::getLevelData()
{
	return mLevelDataReader.getData();
}
