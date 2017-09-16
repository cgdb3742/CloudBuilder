#pragma once
#include "SaveDataReader.h"
#include "GameDataReader.h"
#include "LevelDataReader.h"

class PopUpStack;
class ResourceHandler;

class CompleteData
{
public:
	CompleteData(PopUpStack & popUpStack, ResourceHandler & resourceHandler);
	~CompleteData();

	bool loadSaveData();
	bool loadGameData();
	bool loadLevelData();
	bool loadLevelData(unsigned int world, unsigned int level);

	bool writeLanguage(std::wstring language);
	bool writeMusicVolume(float volume);
	bool writeSoundVolume(float volume);
	bool writeLevelStatus(unsigned int world, unsigned int level, Enums::eLevelStatus status);
	bool writeSavedBoard(unsigned int world, unsigned int level, std::wstring board);

	void processLevelsUnlock();
	void processLevelsUnlock(unsigned int world, unsigned int level);

	SaveData& getSaveData();
	GameData& getGameData();
	LevelData& getLevelData();
private:
	SaveDataReader mSaveDataReader;
	GameDataReader mGameDataReader;
	LevelDataReader mLevelDataReader;

	PopUpStack& mPopUpStack;
	ResourceHandler& mResourceHandler;
};

