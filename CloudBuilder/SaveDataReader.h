#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "Enums.h"

struct SaveData
{
	SaveData() : currentLanguage(L"en") {}

	std::wstring currentLanguage;
	float musicVolume;
	float soundVolume;

	std::vector<std::vector<Enums::eLevelStatus>> levelStatus;//"Locked", "New", "Available", "Complete"
	std::vector<std::vector<std::wstring>> savedBoard;
};

class SaveDataReader
{
public:
	SaveDataReader();
	~SaveDataReader();

	bool readData();
	//TODO Save data

	bool writeLanguage(std::wstring language);
	bool writeMusicVolume(float volume);
	bool writeSoundVolume(float volume);
	bool writeLevelStatus(unsigned int world, unsigned int level, Enums::eLevelStatus status);
	bool writeSavedBoard(unsigned int world, unsigned int level, std::wstring board);

	SaveData& getData();

private:
	SaveData mData;
};

