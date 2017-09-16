#include <iostream>
#include "GameDataReader.h"



GameDataReader::GameDataReader():
	mLanguage(L"en")
{
}

GameDataReader::GameDataReader(std::wstring language):
	mLanguage(language)
{
}


GameDataReader::~GameDataReader()
{
}

void GameDataReader::updateLanguage(std::wstring language)
{
	mLanguage = language;
}

bool GameDataReader::readData()
{
	std::wstring source = L"Data/Game_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		//std::cout << "-" + std::wstring(doc.child("game_data").child("options").child_value("language"))  + "-" << std::endl;

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

		for (pugi::xml_node language : doc.child(L"game_data").child(L"options").children(L"available_language"))
		{
			mData.availableLanguageName.push_back(language.child(L"name").text().as_string());
			mData.availableLanguageTag.push_back(language.child(L"tag").text().as_string());
		}

		for (pugi::xml_node world : doc.child(L"game_data").child(L"levels").children(L"world"))
		{
			//unsigned int worldId = world.attribute("id").as_uint;
			mData.worldName.push_back(world.child(L"name").child(mLanguage.c_str()).text().as_string());
			std::vector<std::wstring> levelName;
			std::vector<std::wstring> levelDescription;
			std::vector<bool> levelIsValidation;
			std::vector<GameData::LevelUnlockPossibilities> levelUnlockRequirements;

			for (pugi::xml_node level : world.children(L"level"))
			{
				levelName.push_back(level.child(L"name").child(mLanguage.c_str()).text().as_string());
				levelDescription.push_back(level.child(L"description").child(mLanguage.c_str()).text().as_string());
				levelIsValidation.push_back(level.child(L"type").text().as_string() == std::wstring(L"validation"));
				levelUnlockRequirements.push_back(readUnlockPossibilities(level.child(L"unlock_requirements").text().as_string()));
			}

			mData.levelName.push_back(levelName);
			mData.levelDescription.push_back(levelDescription);
			mData.levelIsValidation.push_back(levelIsValidation);
			mData.levelUnlockRequirements.push_back(levelUnlockRequirements);
		}

		for (pugi::xml_node instruction : doc.child(L"game_data").child(L"common_translations").children(L"instruction"))
		{
			//TODO Verify the static_cast return a correct value ?
			mData.instructionName.insert(std::pair<Enums::eInstruction, std::wstring>(static_cast<Enums::eInstruction>(instruction.attribute(L"id").as_uint()), instruction.child(mLanguage.c_str()).text().as_string()));
		}

		for (pugi::xml_node instructionModifier : doc.child(L"game_data").child(L"common_translations").children(L"instruction_modifier"))
		{
			mData.instructionModifierName.insert(std::pair<Enums::eInstructionModifier, std::wstring>(static_cast<Enums::eInstructionModifier>(instructionModifier.attribute(L"id").as_uint()), instructionModifier.child(mLanguage.c_str()).text().as_string()));
		}

		for (pugi::xml_node levelTab : doc.child(L"game_data").child(L"common_translations").children(L"level_tab"))
		{
			mData.levelTabName.push_back(levelTab.child(mLanguage.c_str()).text().as_string());
		}

		for (pugi::xml_node instructionModifier : doc.child(L"game_data").child(L"common_translations").children(L"state"))
		{
			mData.stateName.insert(std::pair<Enums::eState, std::wstring>(static_cast<Enums::eState>(instructionModifier.attribute(L"id").as_uint()), instructionModifier.child(mLanguage.c_str()).text().as_string()));
		}

		for (pugi::xml_node result : doc.child(L"game_data").child(L"common_translations").children(L"pop_up"))
		{
			mData.popUpMessage.push_back(result.child(L"message").child(mLanguage.c_str()).text().as_string());
			mData.popUpButton.push_back(result.child(L"button").child(mLanguage.c_str()).text().as_string());
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool GameDataReader::readData(std::wstring language)
{
	mLanguage = language;
	return readData();
}

GameData::LevelUnlockPossibilities GameDataReader::readUnlockPossibilities(std::wstring source)
{
	GameData::LevelUnlockPossibilities res;

	size_t oFound = source.find(L"o");

	while (oFound != std::wstring::npos)
	{
		size_t aFound = source.find(L"a", oFound + 1);

		oFound = source.find(L"o", oFound + 1);

		std::vector<std::pair<unsigned int, unsigned int>> possibility;

		while (aFound != std::wstring::npos && aFound < oFound)
		{
			size_t wFound = source.find(L"w", aFound + 1);
			size_t lFound = source.find(L"l", wFound + 1);

			aFound = source.find(L"a", lFound + 1);

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
