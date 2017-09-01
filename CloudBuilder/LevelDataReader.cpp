#include "LevelDataReader.h"



LevelDataReader::LevelDataReader() :
	mWorld(1),
	mLevel(1),
	mLanguage("en")
{
}

LevelDataReader::LevelDataReader(unsigned int world, unsigned int level) :
	mWorld(world),
	mLevel(level),
	mLanguage("en")
{
}

LevelDataReader::LevelDataReader(std::string language) :
	mWorld(1),
	mLevel(1),
	mLanguage(language)
{
}

LevelDataReader::LevelDataReader(std::string language, unsigned int world, unsigned int level) :
	mWorld(world),
	mLevel(level),
	mLanguage(language)
{
}


LevelDataReader::~LevelDataReader()
{
}

void LevelDataReader::updateLanguage(std::string language)
{
	mLanguage = language;
}

bool LevelDataReader::readData()
{
	std::string source = "Level_" + std::to_string(mWorld) + "_" + std::to_string(mLevel) + ".xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		//TODO get the current language
		//std::string currentLanguage = "en"; //For test purposes only

		mData = LevelData();

		mData.name = doc.child("level_data").child("general_info").child("name").child_value(mLanguage.c_str());
		mData.world = doc.child("level_data").child("general_info").child("world").text().as_uint();
		mData.level = doc.child("level_data").child("general_info").child("puzzle").text().as_uint();
		mData.isValidation = (doc.child("level_data").child("general_info").child_value("type") == std::string("validation"));
		mData.nbRobots = doc.child("level_data").child("general_info").child("robots").text().as_uint();

		for (pugi::xml_node cloud : doc.child("level_data").child("cloud_pictures").children("cloud"))
		{
			mData.clouds.push_back(cloud.child_value("data"));
			mData.results.push_back(cloud.child_value("result"));
		}

		mData.startingBoard = doc.child("level_data").child("board").child_value("starting_data");
		//mData.currentBoard = doc.child("level_data").child("board").child_value("current_data");

		for (pugi::xml_node instruction : doc.child("level_data").child("board").child("available_instructions").children("instruction"))
		{
			mData.availableInstructions.push_back(static_cast<Enums::eInstruction>(instruction.attribute("id").as_uint()));
		}

		for (pugi::xml_node topic : doc.child("level_data").child("infos").children("topic"))
		{
			mData.topics.push_back(topic.child("name").child_value(mLanguage.c_str()));

			std::vector<std::string> infoString;

			for (pugi::xml_node info : topic.children("text"))
			{
				infoString.push_back(info.child_value(mLanguage.c_str()));
			}

			mData.infos.push_back(infoString);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool LevelDataReader::readData(unsigned int newWorld, unsigned int newLevel)
{
	mWorld = newWorld;
	mLevel = newLevel;
	return readData();
}

bool LevelDataReader::readData(std::string language)
{
	mLanguage = language;
	return readData();
}

bool LevelDataReader::readData(std::string language, unsigned int newWorld, unsigned int newLevel)
{
	mLanguage = language;
	mWorld = newWorld;
	mLevel = newLevel;
	return readData();
}

LevelData & LevelDataReader::getData()
{
	return mData;
}
