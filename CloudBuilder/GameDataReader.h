#pragma once
#include <string>
#include <vector>
#include <map>
#include "pugixml.hpp"
#include "Enums.h"

struct GameData
{
	//GameData() : currentLanguage("en") {}
	GameData() {}

	std::vector<std::string> worldName;
	std::vector<std::vector<std::string>> levelName;
	std::vector<std::vector<std::string>> levelDescription;
	std::vector<std::vector<bool>> levelIsValidation;
	//TODO Unlock conditions

	std::vector<std::string> availableLanguages;

	std::map<Enums::eInstruction, std::string> instructionName;
	std::map<Enums::eInstructionModifier, std::string> instructionModifierName;
	std::vector<std::string> levelTabName;
	std::map<Enums::eState, std::string> stateName;
	std::vector<std::string> levelResultMessage;
	std::vector<std::string> levelResultButton;
};

class GameDataReader
{
public:
	GameDataReader();
	GameDataReader(std::string language);
	~GameDataReader();

	void updateLanguage(std::string language);

	bool readData();
	bool readData(std::string language);

	GameData& getData();
private:
	std::string mLanguage;

	GameData mData;
};

