#pragma once
#include "GUIButton.h"
#include "PopUpButton.h"
#include "PopUpStack.h"

class StateMachine;

class PopUpMessage :
	public GUIButton
{
public:
	PopUpMessage(GameContext& gameContext, sf::Vector2f positionRatio, PopUpData messageData);
	~PopUpMessage();

	virtual sf::Vector2f computeChildsBoundingBox();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void updateChildsVector();
private:
	std::string mText;
	PopUpButton mButton;
	sf::Font& mFont;
};

