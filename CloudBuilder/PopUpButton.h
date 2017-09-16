#pragma once
#include "GUIButton.h"
#include "PopUpStack.h"

class StateMachine;

class PopUpButton :
	public GUIButton
{
public:
	PopUpButton(GameContext& gameContext, sf::Vector2f positionRatio, PopUpData messageData);
	~PopUpButton();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void clicked();
private:
	std::wstring mText;
	sf::Font& mFont;
};

