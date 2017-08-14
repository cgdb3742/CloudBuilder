#pragma once
#include <string>
#include <vector>
#include <map>
#include "pugixml.hpp"
#include "Enums.h"

struct GameData
{
	GameData() : currentLanguage("en") {}

	std::vector<std::string> worldName;
	std::vector<std::vector<std::string>> levelName;
	std::vector<std::vector<std::string>> levelDescription;
	std::vector<std::vector<std::string>> levelStatus; //"New", "Available", "Complete" or "Locked"
	//TODO Unlock conditions
	//TODO Create a separate file for saving level status and current interaction boards ?

	std::string currentLanguage;
	std::vector<std::string> availableLanguages;

	std::map<Enums::eInstruction, std::string> instructionName;
	std::map<Enums::eInstructionModifier, std::string> instructionModifierName;
	std::vector<std::string> levelTabName;
};

class GameDataReader
{
public:
	GameDataReader();
	~GameDataReader();

	bool readData();
	//TODO save data

	GameData& getData();
private:
	GameData mData;
};

