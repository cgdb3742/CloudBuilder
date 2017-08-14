#pragma once
#include "GUIButton.h"
#include "Enums.h"

class InstructionPlayer;

class GUIPlayerButton :
	public GUIButton
{
public:
	GUIPlayerButton(GameContext& gameContext, InstructionPlayer& player, Enums::eInstructionPlayerCommand command, sf::Vector2f positionRatio);
	GUIPlayerButton(GameContext& gameContext, InstructionPlayer& player, Enums::eInstructionPlayerCommand playCommand, Enums::eInstructionPlayerCommand pauseCommand, Enums::eInstructionPlayerCommand stopCommand, sf::Vector2f positionRatio);
	~GUIPlayerButton();

	virtual void clicked();

	Enums::eInstructionPlayerCommand getCurrentCommand();
	//virtual void handleEventCurrent(const sf::Event & event);
	virtual void drawCurrent(sf::RenderTarget & target);
	virtual void drawIcon(sf::RenderTarget & target);

	//virtual void setSquareSize(sf::Vector2f newSize);
	//virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);

private:
	Enums::eInstructionPlayerCommand mPlayCommand;
	Enums::eInstructionPlayerCommand mPauseCommand;
	Enums::eInstructionPlayerCommand mStopCommand;

	InstructionPlayer& mPlayer;
	sf::Vector2f mPositionRatio;
};

