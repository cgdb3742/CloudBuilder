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
	std::string source = "Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		mData = SaveData();

		mData.currentLanguage = doc.child("save_data").child("options").child_value("current_language");

		for (pugi::xml_node world : doc.child("save_data").child("levels").children("world")) //TODO Should be read in the right order
		{
			std::vector<std::string> status;
			std::vector<std::string> board;

			for (pugi::xml_node level : world.children("level"))
			{
				status.push_back(level.child_value("status"));
				board.push_back(level.child_value("saved_board"));
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

bool SaveDataReader::writeLanguage(std::string language)
{
	if (language == mData.currentLanguage)
	{
		return false;
	}

	std::string source = "Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		doc.child("save_data").child("options").child("current_language").text().set(language.c_str());
		//std::cout << "Saving new language : " << doc.child("save_data").child("options").child("current_language").text().set(language.c_str()) << std::endl;
		doc.save_file(source.c_str());

		mData.currentLanguage = language;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeLevelStatus(unsigned int world, unsigned int level, std::string status)
{
	if (world > mData.levelStatus.size())
	{
		return false;
	}

	if (level > mData.levelStatus[world - 1].size())
	{
		return false;
	}

	if (status == mData.levelStatus[world-1][level-1])
	{
		return false;
	}

	std::string source = "Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		for (pugi::xml_node worldNode : doc.child("save_data").child("levels").children("world"))
		{
			if (worldNode.attribute("id").as_uint() == world)
			{
				for (pugi::xml_node levelNode : worldNode.children("level"))
				{
					if (levelNode.attribute("id").as_uint() == level)
					{
						levelNode.child("status").text().set(status.c_str());
						//std::cout << "Saving new status : " << levelNode.child("status").set_value(status.c_str()) << std::endl;
					}
				}
			}
		}

		doc.save_file(source.c_str());

		mData.levelStatus[world - 1][level - 1] = status;
		return true;
	}
	else
	{
		return false;
	}
}

bool SaveDataReader::writeSavedBoard(unsigned int world, unsigned int level, std::string board)
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

	std::string source = "Save_data.xml";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source.c_str());

	if (result)
	{
		for (pugi::xml_node worldNode : doc.child("save_data").child("levels").children("world"))
		{
			if (worldNode.attribute("id").as_uint() == world)
			{
				for (pugi::xml_node levelNode : worldNode.children("level"))
				{
					if (levelNode.attribute("id").as_uint() == level)
					{
						levelNode.child("saved_board").text().set(board.c_str());
					}
				}
			}
		}

		doc.save_file(source.c_str());

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
