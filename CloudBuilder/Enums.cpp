#include "Enums.h"
#include "Game.h"



Enums::Enums()
{
}


Enums::~Enums()
{
}

sf::Color Enums::getColor(eColor color)
{
	switch (color)
	{
	case eColor::NoColor: return sf::Color(127, 127, 127);
	case eColor::Red: return sf::Color(255, 0, 0);
	case eColor::Blue: return sf::Color(0, 0, 255);
	case eColor::Green: return sf::Color(0, 255, 0);
	case eColor::Yellow: return sf::Color(255, 255, 0);
	default: return sf::Color(127, 127, 127);
	}

	return sf::Color(127, 127, 127);
}

//Assume the creation order red>blue>green>yellow
bool Enums::isValid(eColor color, GameContext& gameContext)
{
	unsigned int nbRobots = gameContext.levelData.nbRobots;

	switch (color)
	{
	case eColor::NoColor: return true;
	case eColor::Red: return (nbRobots >= 1);
	case eColor::Blue: return (nbRobots >= 2);
	case eColor::Green: return (nbRobots >= 3);
	case eColor::Yellow: return (nbRobots >= 4);
	default: return true;
	}
}

Enums::eInstruction Enums::getInstructionFromString(std::string source)
{
	if (source == "SS")
	{
		return Enums::eInstruction::SpeStart;
	}
	else if (source == "SA")
	{
		return Enums::eInstruction::SpeAccept;
	}
	else if (source == "SR")
	{
		return Enums::eInstruction::SpeReject;
	}
	else if (source == "AM")
	{
		return Enums::eInstruction::ActMove;
	}
	else if (source == "AL")
	{
		return Enums::eInstruction::ActSetCloud;
	}
	else if (source == "AO")
	{
		return Enums::eInstruction::ActSetColor;
	}
	else if (source == "CL")
	{
		return Enums::eInstruction::CheckCloud;
	}
	else if (source == "CO")
	{
		return Enums::eInstruction::CheckColor;
	}
	else if (source == "CB")
	{
		return Enums::eInstruction::CheckBorder;
	}
	else if (source == "FW")
	{
		return Enums::eInstruction::FlowWait;
	}
	else if (source == "FP")
	{
		return Enums::eInstruction::FlowPause;
	}
	else if (source == "FR")
	{
		return Enums::eInstruction::FlowResume;
	}
	else if (source == "FS")
	{
		return Enums::eInstruction::FlowSync;
	}

	return Enums::eInstruction::Unassigned;
}

Enums::eColor Enums::getColorFromString(char source)
{
	if (source == 'n')
	{
		return Enums::eColor::NoColor;
	}
	else if (source == 'r')
	{
		return Enums::eColor::Red;
	}
	else if (source == 'b')
	{
		return Enums::eColor::Blue;
	}
	else if (source == 'g')
	{
		return Enums::eColor::Green;
	}
	else if (source == 'y')
	{
		return Enums::eColor::Yellow;
	}

	return Enums::eColor::NoColor;
}

Enums::eDir Enums::getDirFromString(char source)
{
	if (source == 'c')
	{
		return Enums::eDir::Center;
	}
	else if (source == 'l')
	{
		return Enums::eDir::Left;
	}
	else if (source == 'r')
	{
		return Enums::eDir::Right;
	}
	else if (source == 'u')
	{
		return Enums::eDir::Up;
	}
	else if (source == 'd')
	{
		return Enums::eDir::Down;
	}

	return Enums::eDir::Center;
}

bool Enums::getBoolFromString(char source)
{
	return (source == '1');
}

std::string Enums::getString(eInstruction instruction)
{
	switch (instruction)
	{
	case Enums::eInstruction::Unassigned: return "UU";
	case Enums::eInstruction::SpeStart: return "SS";
	case Enums::eInstruction::SpeAccept: return "SA";
	case Enums::eInstruction::SpeReject: return "SR";
	case Enums::eInstruction::ActMove: return "AM";
	case Enums::eInstruction::ActSetCloud: return "AL";
	case Enums::eInstruction::ActSetColor: return "AO";
	case Enums::eInstruction::CheckCloud: return "CL";
	case Enums::eInstruction::CheckColor: return "CO";
	case Enums::eInstruction::CheckBorder: return "CB";
	case Enums::eInstruction::FlowWait: return "FW";
	case Enums::eInstruction::FlowPause: return "FP";
	case Enums::eInstruction::FlowResume: return "FR";
	case Enums::eInstruction::FlowSync: return "FS";
	default: return "UU";
	}
}

char Enums::getString(eColor color)
{
	switch (color)
	{
	case Enums::eColor::NoColor: return 'n';
	case Enums::eColor::Red: return 'r';
	case Enums::eColor::Blue: return 'b';
	case Enums::eColor::Green: return 'g';
	case Enums::eColor::Yellow: return 'y';
	default: return 'n';
	}
}

char Enums::getString(eDir dir)
{
	switch (dir)
	{
	case Enums::eDir::Center: return 'c';
	case Enums::eDir::Left: return 'l';
	case Enums::eDir::Right: return 'r';
	case Enums::eDir::Up: return 'u';
	case Enums::eDir::Down: return 'd';
	default: return 'c';
	}
}

char Enums::getString(bool value)
{
	return (value ? '1' : '0');
}
