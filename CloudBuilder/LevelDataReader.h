#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "Enums.h"
#include "MusicHandler.h"

struct LevelData
{
	//LevelData() : name(""), world(1), level(1), isValidation(true), nbRobots(1), startingBoard(""), currentBoard("") {}
	LevelData() : name(L""), world(1), level(1), isValidation(true), nbRobots(1), startingBoard(L"") {}

	std::wstring name;
	unsigned int world;
	unsigned int level;
	bool isValidation; //true if validation, false if modification
	unsigned int nbRobots;
	MusicHandler::eMusic music;

	std::vector<std::wstring> clouds;
	std::vector<std::wstring> results; //TODO hold Accept or Reject if validation, final clouds if modification ?

	std::wstring startingBoard;
	std::vector<Enums::eInstruction> availableInstructions;

	std::vector<std::wstring> topics;
	std::vector<std::vector<std::wstring>> infos;
};

class LevelDataReader
{
public:
	LevelDataReader();
	LevelDataReader(unsigned int world, unsigned int level);
	LevelDataReader(std::wstring language);
	LevelDataReader(std::wstring language, unsigned int world, unsigned int level);
	~LevelDataReader();

	void updateLanguage(std::wstring language);

	bool readData();
	bool readData(unsigned int newWorld, unsigned int newLevel);
	bool readData(std::wstring language);
	bool readData(std::wstring language, unsigned int newWorld, unsigned int newLevel);

	LevelData& getData();

private:
	unsigned int mWorld;
	unsigned int mLevel;

	std::wstring mLanguage;

	LevelData mData;
};

