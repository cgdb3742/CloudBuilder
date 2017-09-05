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

bool CompleteData::writeLanguage(std::string language)
{
	if (mSaveDataReader.writeLanguage(language))
	{
		mGameDataReader.updateLanguage(language);
		loadGameData();
		mLevelDataReader.updateLanguage(language);
		loadLevelData();

		//Each object should update its translation on its own

		return true;
	}
	else
	{
		return false;
	}
}

bool CompleteData::writeLevelStatus(unsigned int world, unsigned int level, std::string status)
{
	if (mSaveDataReader.writeLevelStatus(world, level, status))
	{
		//TODO Process level unlocks if necessary
		return true;
	}
	else
	{
		return false;
	}
}

bool CompleteData::writeSavedBoard(unsigned int world, unsigned int level, std::string board)
{
	if (mSaveDataReader.writeSavedBoard(world, level, board))
	{
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
