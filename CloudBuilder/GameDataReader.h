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

	std::vector<std::wstring> worldName;
	std::vector<std::vector<std::wstring>> levelName;
	std::vector<std::vector<std::wstring>> levelDescription;
	std::vector<std::vector<bool>> levelIsValidation;
	std::vector<std::vector<LevelUnlockPossibilities>> levelUnlockRequirements;

	std::vector<std::wstring> availableLanguageName;
	std::vector<std::wstring> availableLanguageTag;

	std::map<Enums::eInstruction, std::wstring> instructionName;
	std::map<Enums::eInstructionModifier, std::wstring> instructionModifierName;
	std::vector<std::wstring> levelTabName;
	std::map<Enums::eState, std::wstring> stateName;
	std::vector<std::wstring> popUpMessage;
	std::vector<std::wstring> popUpButton;
};

class GameDataReader
{
public:
	GameDataReader();
	GameDataReader(std::wstring language);
	~GameDataReader();

	void updateLanguage(std::wstring language);

	bool readData();
	bool readData(std::wstring language);

	GameData::LevelUnlockPossibilities readUnlockPossibilities(std::wstring source);

	GameData& getData();
private:
	std::wstring mLanguage;

	GameData mData;
};

