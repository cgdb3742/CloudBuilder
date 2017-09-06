#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "Enums.h"

struct SaveData
{
	SaveData() : currentLanguage("en") {}

	std::string currentLanguage;

	std::vector<std::vector<Enums::eLevelStatus>> levelStatus;//"Locked", "New", "Available", "Complete"
	std::vector<std::vector<std::string>> savedBoard;
};

class SaveDataReader
{
public:
	SaveDataReader();
	~SaveDataReader();

	bool readData();
	//TODO Save data

	bool writeLanguage(std::string language);
	bool writeLevelStatus(unsigned int world, unsigned int level, Enums::eLevelStatus status);
	bool writeSavedBoard(unsigned int world, unsigned int level, std::string board);

	SaveData& getData();

private:
	SaveData mData;
};

