#include <iostream>
#include "GameDataReader.h"



GameDataReader::GameDataReader():
	mLanguage("en")
{
}

GameDataReader::GameDataReader(std::string language):
	mLanguage(language)
{
}


GameDataReader::~GameDataReader()
{
}

void GameDataReader::updateLanguage(std::string language)
{
	mLanguage = language;
}

bool GameDataReader::readData()
{
	std::string source = "Game_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		//std::cout << "-" + std::string(doc.child("game_data").child("options").child_value("language"))  + "-" << std::endl;

		//pugi::xml_node translations = doc.child("game_data").child("common_translations");

		//for (pugi::xml_node inst : translations.children("instruction"))
		//{
		//	std::cout << "Instruction:";

		//	for (pugi::xml_attribute attr : inst.attributes())
		//	{
		//		std::cout << " " << attr.name() << "=" << attr.value();
		//	}

		//	std::cout << std::endl;
		//}

		mData = GameData();

		//mData.currentLanguage = doc.child("game_data").child("options").child_value("current_language");
		//std::string currentLanguage = "en"; //TODO Get current language

		for (pugi::xml_node language : doc.child("game_data").child("options").children("available_language"))
		{
			mData.availableLanguageName.push_back(language.child_value("name"));
			mData.availableLanguageTag.push_back(language.child_value("tag"));
		}

		for (pugi::xml_node world : doc.child("game_data").child("levels").children("world"))
		{
			//unsigned int worldId = world.attribute("id").as_uint;
			mData.worldName.push_back(world.child("name").child_value(mLanguage.c_str()));
			std::vector<std::string> levelName;
			std::vector<std::string> levelDescription;
			std::vector<bool> levelIsValidation;
			std::vector<GameData::LevelUnlockPossibilities> levelUnlockRequirements;

			for (pugi::xml_node level : world.children("level"))
			{
				levelName.push_back(level.child("name").child_value(mLanguage.c_str()));
				levelDescription.push_back(level.child("description").child_value(mLanguage.c_str()));
				levelIsValidation.push_back(level.child_value("type") == std::string("validation"));
				levelUnlockRequirements.push_back(readUnlockPossibilities(level.child_value("unlock_requirements")));
			}

			mData.levelName.push_back(levelName);
			mData.levelDescription.push_back(levelDescription);
			mData.levelIsValidation.push_back(levelIsValidation);
			mData.levelUnlockRequirements.push_back(levelUnlockRequirements);
		}

		for (pugi::xml_node instruction : doc.child("game_data").child("common_translations").children("instruction"))
		{
			//TODO Verify the static_cast return a correct value ?
			mData.instructionName.insert(std::pair<Enums::eInstruction, std::string>(static_cast<Enums::eInstruction>(instruction.attribute("id").as_uint()), instruction.child_value(mLanguage.c_str())));
		}

		for (pugi::xml_node instructionModifier : doc.child("game_data").child("common_translations").children("instruction_modifier"))
		{
			mData.instructionModifierName.insert(std::pair<Enums::eInstructionModifier, std::string>(static_cast<Enums::eInstructionModifier>(instructionModifier.attribute("id").as_uint()), instructionModifier.child_value(mLanguage.c_str())));
		}

		for (pugi::xml_node levelTab : doc.child("game_data").child("common_translations").children("level_tab"))
		{
			mData.levelTabName.push_back(levelTab.child_value(mLanguage.c_str()));
		}

		for (pugi::xml_node instructionModifier : doc.child("game_data").child("common_translations").children("state"))
		{
			mData.stateName.insert(std::pair<Enums::eState, std::string>(static_cast<Enums::eState>(instructionModifier.attribute("id").as_uint()), instructionModifier.child_value(mLanguage.c_str())));
		}

		for (pugi::xml_node result : doc.child("game_data").child("common_translations").children("pop_up"))
		{
			mData.popUpMessage.push_back(result.child("message").child_value(mLanguage.c_str()));
			mData.popUpButton.push_back(result.child("button").child_value(mLanguage.c_str()));
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool GameDataReader::readData(std::string language)
{
	mLanguage = language;
	return readData();
}

GameData::LevelUnlockPossibilities GameDataReader::readUnlockPossibilities(std::string source)
{
	GameData::LevelUnlockPossibilities res;

	size_t oFound = source.find("o");

	while (oFound != std::string::npos)
	{
		size_t aFound = source.find("a", oFound + 1);

		oFound = source.find("o", oFound + 1);

		std::vector<std::pair<unsigned int, unsigned int>> possibility;

		while (aFound != std::string::npos && aFound < oFound)
		{
			size_t wFound = source.find("w", aFound + 1);
			size_t lFound = source.find("l", wFound + 1);

			aFound = source.find("a", lFound + 1);

			unsigned int w = stoul(source.substr(wFound + 1, wFound - lFound - 1));
			unsigned int l = stoul(source.substr(lFound + 1, lFound - std::min(oFound, aFound) - 1));

			possibility.push_back(std::pair<unsigned int, unsigned int>(w, l));
		}

		res.push_back(possibility);
	}

	return res;
}

GameData & GameDataReader::getData()
{
	return mData;
}
