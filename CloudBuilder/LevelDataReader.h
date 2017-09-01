#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "Enums.h"

struct LevelData
{
	//LevelData() : name(""), world(1), level(1), isValidation(true), nbRobots(1), startingBoard(""), currentBoard("") {}
	LevelData() : name(""), world(1), level(1), isValidation(true), nbRobots(1), startingBoard("") {}

	std::string name;
	unsigned int world;
	unsigned int level;
	bool isValidation; //true if validation, false if modification
	unsigned int nbRobots;

	std::vector<std::string> clouds;
	std::vector<std::string> results; //TODO hold Accept or Reject if validation, final clouds if modification ?

	std::string startingBoard;
	std::vector<Enums::eInstruction> availableInstructions;

	std::vector<std::string> topics;
	std::vector<std::vector<std::string>> infos;
};

class LevelDataReader
{
public:
	LevelDataReader();
	LevelDataReader(unsigned int world, unsigned int level);
	LevelDataReader(std::string language);
	LevelDataReader(std::string language, unsigned int world, unsigned int level);
	~LevelDataReader();

	void updateLanguage(std::string language);

	bool readData();
	bool readData(unsigned int newWorld, unsigned int newLevel);
	bool readData(std::string language);
	bool readData(std::string language, unsigned int newWorld, unsigned int newLevel);

	LevelData& getData();

private:
	unsigned int mWorld;
	unsigned int mLevel;

	std::string mLanguage;

	LevelData mData;
};

