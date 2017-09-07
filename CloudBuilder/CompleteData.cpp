#include "CompleteData.h"
#include "PopUpStack.h"



CompleteData::CompleteData(PopUpStack & popUpStack):
	mSaveDataReader(),
	mGameDataReader(),
	mLevelDataReader(),
	mPopUpStack(popUpStack)
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

bool CompleteData::writeLevelStatus(unsigned int world, unsigned int level, Enums::eLevelStatus status)
{
	if (mSaveDataReader.writeLevelStatus(world, level, status))
	{
		//Process level unlocks if necessary
		if (status == Enums::eLevelStatus::Complete)
		{
			processLevelsUnlock();
		}
		if (status == Enums::eLevelStatus::New)
		{
			mPopUpStack.addMessage(mGameDataReader.getData().popUpMessage[4] + std::to_string(world) + "-" + std::to_string(level) + " : " + mGameDataReader.getData().levelName[world - 1][level - 1], mGameDataReader.getData().popUpButton[4]);
		}

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
		mPopUpStack.addMessage(mGameDataReader.getData().popUpMessage[3], mGameDataReader.getData().popUpButton[3]);

		return true;
	}
	else
	{
		return false;
	}
}

void CompleteData::processLevelsUnlock()
{
	for (unsigned int world = 0; world < mGameDataReader.getData().levelUnlockRequirements.size(); world++)
	{
		for (unsigned int level = 0; level < mGameDataReader.getData().levelUnlockRequirements[world].size(); level++)
		{
			if (mSaveDataReader.getData().levelStatus[world][level] == Enums::eLevelStatus::Locked)
			{
				processLevelsUnlock(world + 1, level + 1);
			}
		}
	}
}

void CompleteData::processLevelsUnlock(unsigned int world, unsigned int level)
{
	for (std::vector<std::pair<unsigned int, unsigned int>> possibility : mGameDataReader.getData().levelUnlockRequirements[world - 1][level - 1])
	{
		bool possibilityVerified(true);
		unsigned int i = 0;

		while (possibilityVerified && i < possibility.size())
		{
			possibilityVerified = (mSaveDataReader.getData().levelStatus[possibility[i].first - 1][possibility[i].second - 1] == Enums::eLevelStatus::Complete);
			i++;
		}

		if (possibilityVerified)
		{
			writeLevelStatus(world, level, Enums::eLevelStatus::New);

			return;
		}
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
