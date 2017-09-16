#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct GameContext;

class Enums
{
public:
	enum eState
	{
		Undefined = 0,
		TitleScreen = 1,
		MainMenu = 2,
		LevelSelect = 3,
		Level = 4,
		Pause = 5,
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

	enum eLevelStatus
	{
		Locked = 0,
		New = 1,
		Available = 2,
		Complete = 3
	};

	Enums();
	~Enums();

	static sf::Color getColor(eColor color);
	static bool isValid(eColor color, GameContext& gameContext); //Get if the robot color is allowed in the given level context in gameContext

	static eInstruction getInstructionFromString(std::wstring source);
	static eColor getColorFromString(wchar_t source);
	static eDir getDirFromString(wchar_t source);
	static bool getBoolFromString(wchar_t source);
	static std::wstring getString(eInstruction instruction);
	static wchar_t getString(eColor color);
	static wchar_t getString(eDir dir);
	static wchar_t getString(bool value);
};

