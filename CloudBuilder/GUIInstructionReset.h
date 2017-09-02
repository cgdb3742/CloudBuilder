#pragma once
#include "GUIButton.h"

class Level;

class GUIInstructionReset :
	public GUIButton
{
public:
	GUIInstructionReset(GameContext& gameContext, sf::Vector2f positionRatio, Level& level);
	GUIInstructionReset(GameContext& gameContext, Level& level);
	~GUIInstructionReset();

	virtual void clicked();

	virtual void drawCurrent(sf::RenderTarget & target);
private:
	Level& mLevel;
};

