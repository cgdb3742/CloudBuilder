#pragma once
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "Enums.h"

struct LevelData
{
	LevelData() : name(""), world(1), level(1), isValidation(true), nbRobots(1), startingBoard(""), currentBoard("") {}

	std::string name;
	unsigned int world;
	unsigned int level;
	bool isValidation; //true if validation, false if modification
	unsigned int nbRobots;

	std::vector<std::string> clouds;
	std::vector<std::string> results; //TODO hold Accept or Reject if validation, final clouds if modification ?

	std::string startingBoard;
	std::vector<Enums::eInstruction> availableInstructions;
	std::string currentBoard;

	std::vector<std::string> topics;
	std::vector<std::vector<std::string>> infos;
};

class LevelDataReader
{
public:
	LevelDataReader();
	LevelDataReader(unsigned int world, unsigned int level);
	~LevelDataReader();

	bool readData();
	//TODO save data

private:
	unsigned int mWorld;
	unsigned int mLevel;

	LevelData mData;
};

