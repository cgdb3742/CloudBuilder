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

Enums::eInstruction Enums::getInstructionFromString(std::wstring source)
{
	if (source == L"SS")
	{
		return Enums::eInstruction::SpeStart;
	}
	else if (source == L"SA")
	{
		return Enums::eInstruction::SpeAccept;
	}
	else if (source == L"SR")
	{
		return Enums::eInstruction::SpeReject;
	}
	else if (source == L"AM")
	{
		return Enums::eInstruction::ActMove;
	}
	else if (source == L"AL")
	{
		return Enums::eInstruction::ActSetCloud;
	}
	else if (source == L"AO")
	{
		return Enums::eInstruction::ActSetColor;
	}
	else if (source == L"CL")
	{
		return Enums::eInstruction::CheckCloud;
	}
	else if (source == L"CO")
	{
		return Enums::eInstruction::CheckColor;
	}
	else if (source == L"CB")
	{
		return Enums::eInstruction::CheckBorder;
	}
	else if (source == L"FW")
	{
		return Enums::eInstruction::FlowWait;
	}
	else if (source == L"FP")
	{
		return Enums::eInstruction::FlowPause;
	}
	else if (source == L"FR")
	{
		return Enums::eInstruction::FlowResume;
	}
	else if (source == L"FS")
	{
		return Enums::eInstruction::FlowSync;
	}

	return Enums::eInstruction::Unassigned;
}

Enums::eColor Enums::getColorFromString(wchar_t source)
{
	if (source == L'n')
	{
		return Enums::eColor::NoColor;
	}
	else if (source == L'r')
	{
		return Enums::eColor::Red;
	}
	else if (source == L'b')
	{
		return Enums::eColor::Blue;
	}
	else if (source == L'g')
	{
		return Enums::eColor::Green;
	}
	else if (source == L'y')
	{
		return Enums::eColor::Yellow;
	}

	return Enums::eColor::NoColor;
}

Enums::eDir Enums::getDirFromString(wchar_t source)
{
	if (source == L'c')
	{
		return Enums::eDir::Center;
	}
	else if (source == L'l')
	{
		return Enums::eDir::Left;
	}
	else if (source == L'r')
	{
		return Enums::eDir::Right;
	}
	else if (source == L'u')
	{
		return Enums::eDir::Up;
	}
	else if (source == L'd')
	{
		return Enums::eDir::Down;
	}

	return Enums::eDir::Center;
}

bool Enums::getBoolFromString(wchar_t source)
{
	return (source == L'1');
}

std::wstring Enums::getString(eInstruction instruction)
{
	switch (instruction)
	{
	case Enums::eInstruction::Unassigned: return L"UU";
	case Enums::eInstruction::SpeStart: return L"SS";
	case Enums::eInstruction::SpeAccept: return L"SA";
	case Enums::eInstruction::SpeReject: return L"SR";
	case Enums::eInstruction::ActMove: return L"AM";
	case Enums::eInstruction::ActSetCloud: return L"AL";
	case Enums::eInstruction::ActSetColor: return L"AO";
	case Enums::eInstruction::CheckCloud: return L"CL";
	case Enums::eInstruction::CheckColor: return L"CO";
	case Enums::eInstruction::CheckBorder: return L"CB";
	case Enums::eInstruction::FlowWait: return L"FW";
	case Enums::eInstruction::FlowPause: return L"FP";
	case Enums::eInstruction::FlowResume: return L"FR";
	case Enums::eInstruction::FlowSync: return L"FS";
	default: return L"UU";
	}
}

wchar_t Enums::getString(eColor color)
{
	switch (color)
	{
	case Enums::eColor::NoColor: return L'n';
	case Enums::eColor::Red: return L'r';
	case Enums::eColor::Blue: return L'b';
	case Enums::eColor::Green: return L'g';
	case Enums::eColor::Yellow: return L'y';
	default: return L'n';
	}
}

wchar_t Enums::getString(eDir dir)
{
	switch (dir)
	{
	case Enums::eDir::Center: return L'c';
	case Enums::eDir::Left: return L'l';
	case Enums::eDir::Right: return L'r';
	case Enums::eDir::Up: return L'u';
	case Enums::eDir::Down: return L'd';
	default: return L'c';
	}
}

wchar_t Enums::getString(bool value)
{
	return (value ? L'1' : L'0');
}
