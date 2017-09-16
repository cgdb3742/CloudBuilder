#include <iostream>
#include "SaveDataReader.h"



SaveDataReader::SaveDataReader()
{
}


SaveDataReader::~SaveDataReader()
{
}

bool SaveDataReader::readData()
{
	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		mData = SaveData();

		mData.currentLanguage = doc.child(L"save_data").child(L"options").child_value(L"current_language");
		mData.musicVolume = doc.child(L"save_data").child(L"options").child(L"music_volume").text().as_float();
		mData.soundVolume = doc.child(L"save_data").child(L"options").child(L"sound_volume").text().as_float();

		for (pugi::xml_node world : doc.child(L"save_data").child(L"levels").children(L"world")) //TODO Should be read in the right order
		{
			std::vector<Enums::eLevelStatus> status;
			std::vector<std::wstring> board;

			for (pugi::xml_node level : world.children(L"level"))
			{
				status.push_back(static_cast<Enums::eLevelStatus>(level.child(L"status").text().as_uint()));
				board.push_back(level.child_value(L"saved_board"));
			}

			mData.levelStatus.push_back(status);
			mData.savedBoard.push_back(board);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeLanguage(std::wstring language)
{
	if (language == mData.currentLanguage)
	{
		return false;
	}

	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		doc.child(L"save_data").child(L"options").child(L"current_language").text().set(language.c_str());
		//std::cout << "Saving new language : " << doc.child(L"save_data").child(L"options").child(L"current_language").text().set(language.c_str()) << std::endl;
		doc.save_file(source.c_str(), L"\t", pugi::format_default, pugi::xml_encoding::encoding_latin1);

		mData.currentLanguage = language;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeMusicVolume(float volume)
{
	if (volume == mData.musicVolume)
	{
		return false;
	}

	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		doc.child(L"save_data").child(L"options").child(L"music_volume").text().set(volume);
		doc.save_file(source.c_str(), L"\t", pugi::format_default, pugi::xml_encoding::encoding_latin1);

		mData.musicVolume = volume;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeSoundVolume(float volume)
{
	if (volume == mData.soundVolume)
	{
		return false;
	}

	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		doc.child(L"save_data").child(L"options").child(L"sound_volume").text().set(volume);
		doc.save_file(source.c_str(), L"\t", pugi::format_default, pugi::xml_encoding::encoding_latin1);

		mData.soundVolume = volume;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeLevelStatus(unsigned int world, unsigned int level, Enums::eLevelStatus status)
{
	if (world > mData.levelStatus.size())
	{
		return false;
	}

	if (level > mData.levelStatus[world - 1].size())
	{
		return false;
	}

	//Complete > Available > New > Locked
	if (status <= mData.levelStatus[world-1][level-1])
	{
		return false;
	}

	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		for (pugi::xml_node worldNode : doc.child(L"save_data").child(L"levels").children(L"world"))
		{
			if (worldNode.attribute(L"id").as_uint() == world)
			{
				for (pugi::xml_node levelNode : worldNode.children(L"level"))
				{
					if (levelNode.attribute(L"id").as_uint() == level)
					{
						levelNode.child(L"status").text().set(status);
						//std::cout << "Saving new status : " << levelNode.child(L"status").set_value(status.c_str()) << std::endl;
					}
				}
			}
		}

		doc.save_file(source.c_str(), L"\t", pugi::format_default, pugi::xml_encoding::encoding_latin1);

		mData.levelStatus[world - 1][level - 1] = status;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeSavedBoard(unsigned int world, unsigned int level, std::wstring board)
{
	if (world > mData.savedBoard.size())
	{
		return false;
	}

	if (level > mData.savedBoard[world - 1].size())
	{
		return false;
	}

	if (board == mData.savedBoard[world - 1][level - 1])
	{
		return false;
	}

	std::wstring source = L"Data/Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str(), pugi::parse_default, pugi::xml_encoding::encoding_latin1);

	if (result)
	{
		for (pugi::xml_node worldNode : doc.child(L"save_data").child(L"levels").children(L"world"))
		{
			if (worldNode.attribute(L"id").as_uint() == world)
			{
				for (pugi::xml_node levelNode : worldNode.children(L"level"))
				{
					if (levelNode.attribute(L"id").as_uint() == level)
					{
						levelNode.child(L"saved_board").text().set(board.c_str());
					}
				}
			}
		}

		doc.save_file(source.c_str(), L"\t", pugi::format_default, pugi::xml_encoding::encoding_latin1);

		mData.savedBoard[world - 1][level - 1] = board;
		return true;
	}
	else
	{
		return false;
	}
}

SaveData & SaveDataReader::getData()
{
	return mData;
}
