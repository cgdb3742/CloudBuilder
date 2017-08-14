#include <iostream>
#include "GameDataReader.h"



GameDataReader::GameDataReader()
{
}


GameDataReader::~GameDataReader()
{
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

		mData.currentLanguage = doc.child("game_data").child("options").child_value("current_language");

		for (pugi::xml_node language : doc.child("game_data").child("options").children("available_language"))
		{
			mData.availableLanguages.push_back(language.text().as_string());
		}

		for (pugi::xml_node world : doc.child("game_data").child("levels").children("world"))
		{
			//unsigned int worldId = world.attribute("id").as_uint;
			mData.worldName.push_back(world.child("name").child_value(mData.currentLanguage.c_str()));
			std::vector<std::string> levelName;
			std::vector<std::string> levelDescription;

			for (pugi::xml_node level : world.children("level"))
			{
				levelName.push_back(level.child("name").child_value(mData.currentLanguage.c_str()));
				levelDescription.push_back(level.child("description").child_value(mData.currentLanguage.c_str()));
			}

			mData.levelName.push_back(levelName);
			mData.levelDescription.push_back(levelDescription);
		}

		for (pugi::xml_node instruction : doc.child("game_data").child("common_translations").children("instruction"))
		{
			//TODO Verify the static_cast return a correct value ?
			mData.instructionName.insert(std::pair<Enums::eInstruction, std::string>(static_cast<Enums::eInstruction>(instruction.attribute("id").as_uint()), instruction.child_value(mData.currentLanguage.c_str())));
		}

		for (pugi::xml_node instructionModifier : doc.child("game_data").child("common_translations").children("instruction_modifier"))
		{
			mData.instructionModifierName.insert(std::pair<Enums::eInstructionModifier, std::string>(static_cast<Enums::eInstructionModifier>(instructionModifier.attribute("id").as_uint()), instructionModifier.child_value(mData.currentLanguage.c_str())));
		}

		for (pugi::xml_node levelTab : doc.child("game_data").child("common_translations").children("level_tab"))
		{
			mData.levelTabName.push_back(levelTab.child_value(mData.currentLanguage.c_str()));
		}

		for (pugi::xml_node result : doc.child("game_data").child("common_translations").children("pop_up"))
		{
			mData.levelResultMessage.push_back(result.child("message").child_value(mData.currentLanguage.c_str()));
			mData.levelResultButton.push_back(result.child("button").child_value(mData.currentLanguage.c_str()));
		}

		return true;
	}
	else
	{
		return false;
	}
}

GameData & GameDataReader::getData()
{
	return mData;
}
