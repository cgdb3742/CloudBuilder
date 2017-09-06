#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "pugixml.hpp"
#include "Enums.h"

struct GameData
{
	//Represents (x AND x AND x AND ... AND x) OR (x AND x AND x AND ... AND x) OR ... OR (x AND x AND x AND ... AND x)
	typedef std::vector<std::vector<std::pair<unsigned int, unsigned int>>> LevelUnlockPossibilities;

	//GameData() : currentLanguage("en") {}
	GameData() {}

	std::vector<std::string> worldName;
	std::vector<std::vector<std::string>> levelName;
	std::vector<std::vector<std::string>> levelDescription;
	std::vector<std::vector<bool>> levelIsValidation;
	std::vector<std::vector<LevelUnlockPossibilities>> levelUnlockRequirements;

	std::vector<std::string> availableLanguageName;
	std::vector<std::string> availableLanguageTag;

	std::map<Enums::eInstruction, std::string> instructionName;
	std::map<Enums::eInstructionModifier, std::string> instructionModifierName;
	std::vector<std::string> levelTabName;
	std::map<Enums::eState, std::string> stateName;
	std::vector<std::string> popUpMessage;
	std::vector<std::string> popUpButton;
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

	GameData::LevelUnlockPossibilities readUnlockPossibilities(std::string source);

	GameData& getData();
private:
	std::string mLanguage;

	GameData mData;
};

