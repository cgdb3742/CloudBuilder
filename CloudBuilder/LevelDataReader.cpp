#include "LevelDataReader.h"



LevelDataReader::LevelDataReader() :
	mWorld(1),
	mLevel(1),
	mLanguage(L"en")
{
}

LevelDataReader::LevelDataReader(unsigned int world, unsigned int level) :
	mWorld(world),
	mLevel(level),
	mLanguage(L"en")
{
}

LevelDataReader::LevelDataReader(std::wstring language) :
	mWorld(1),
	mLevel(1),
	mLanguage(language)
{
}

LevelDataReader::LevelDataReader(std::wstring language, unsigned int world, unsigned int level) :
	mWorld(world),
	mLevel(level),
	mLanguage(language)
{
}


LevelDataReader::~LevelDataReader()
{
}

void LevelDataReader::updateLanguage(std::wstring language)
{
	mLanguage = language;
}

bool LevelDataReader::readData()
{
	std::wstring source = L"Data/Level_" + std::to_wstring(mWorld) + L"_" + std::to_wstring(mLevel) + L".xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		//TODO get the current language
		//std::wstring currentLanguage = "en"; //For test purposes only

		mData = LevelData();

		mData.name = doc.child(L"level_data").child(L"general_info").child(L"name").child_value(mLanguage.c_str());
		mData.world = doc.child(L"level_data").child(L"general_info").child(L"world").text().as_uint();
		mData.level = doc.child(L"level_data").child(L"general_info").child(L"level").text().as_uint();
		mData.isValidation = (doc.child(L"level_data").child(L"general_info").child_value(L"type") == std::wstring(L"validation"));
		mData.nbRobots = doc.child(L"level_data").child(L"general_info").child(L"robots").text().as_uint();
		mData.music = static_cast<MusicHandler::eMusic>(doc.child(L"level_data").child(L"general_info").child(L"music_id").text().as_uint());

		for (pugi::xml_node cloud : doc.child(L"level_data").child(L"cloud_pictures").children(L"cloud"))
		{
			mData.clouds.push_back(cloud.child_value(L"data"));
			mData.results.push_back(cloud.child_value(L"result"));
		}

		mData.startingBoard = doc.child(L"level_data").child(L"board").child_value(L"starting_data");
		//mData.currentBoard = doc.child("level_data").child("board").child_value("current_data");

		for (pugi::xml_node instruction : doc.child(L"level_data").child(L"board").child(L"available_instructions").children(L"instruction"))
		{
			mData.availableInstructions.push_back(static_cast<Enums::eInstruction>(instruction.attribute(L"id").as_uint()));
		}

		for (pugi::xml_node topic : doc.child(L"level_data").child(L"infos").children(L"topic"))
		{
			mData.topics.push_back(topic.child(L"name").child_value(mLanguage.c_str()));

			std::vector<std::wstring> infoString;

			for (pugi::xml_node info : topic.children(L"text"))
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

bool LevelDataReader::readData(std::wstring language)
{
	mLanguage = language;
	return readData();
}

bool LevelDataReader::readData(std::wstring language, unsigned int newWorld, unsigned int newLevel)
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
