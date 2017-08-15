#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Enums
{
public:
	enum eState
	{
		Undefined = 0,
		TitleScreen = 1,
		MainMenu = 2,
		Pause = 3,
		LevelSelect = 4,
		Level = 5,
		PopUp = 6
	};

	enum eInstruction
	{
		Unassigned = 0,
		SpeStart = 11,
		SpeAccept = 12,
		SpeReject = 13,
		ActMove = 21,
		ActSetCloud = 22,
		ActSetColor = 23,
		CheckCloud = 31,
		CheckColor = 32,
		CheckBorder = 33,
		FlowWait = 41,
		FlowPause = 42,
		FlowResume = 43,
		FlowSync = 44
	};

	enum eInstructionModifier
	{
		Unknown = 0,
		NextDir = 11,
		NextDirTrue = 12,
		NextDirFalse = 13,
		CheckDir = 14,
		CloudDir = 15,
		RobotColor = 21,
		CloudColor = 22,
		CloudBool = 31
	};

	enum eColor
	{
		NoColor = 0,
		Red = 1,
		Blue = 2,
		Green = 3,
		Yellow = 4
	};

	enum eDir
	{
		Center = 0,
		Right = 1,
		Up = 2,
		Left = 3,
		Down = 4
	};

	enum eInstructionPlayerCommand
	{
		CmdUnknown = 0,
		CmdPlay = 1,
		CmdStop = 2,
		CmdPause = 3,
		CmdStep = 4,
		CmdSpeedSlow = 5,
		CmdSpeedMedium = 6,
		CmdSpeedFast = 7,
		CmdSpeedInstant = 8
	};

	enum eResult
	{
		Running = 0,
		Accept = 1,
		Refuse = 2,
		Submit = 3
	};

	Enums();
	~Enums();

	static sf::Color getColor(eColor color);

	static eInstruction getInstructionFromString(std::string source);
	static eColor getColorFromString(char source);
	static eDir getDirFromString(char source);
	static bool getBoolFromString(char source);
	static std::string getString(eInstruction instruction);
	static char getString(eColor color);
	static char getString(eDir dir);
	static char getString(bool value);
};

