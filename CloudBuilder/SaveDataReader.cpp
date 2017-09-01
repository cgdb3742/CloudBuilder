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

		for (pugi::xml_node world : doc.child("save_data").children("world")) //TODO Should be read in the right order
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

SaveData & SaveDataReader::getData()
{
	return mData;
}
