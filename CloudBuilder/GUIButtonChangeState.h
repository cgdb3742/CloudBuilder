#pragma once
#include "GUIButton.h"
#include "Enums.h"
class GUIButtonChangeState :
	public GUIButton
{
public:
	GUIButtonChangeState(GameContext& gameContext, sf::Vector2f positionRatio, Enums::eState currentState, Enums::eState newState, sf::Color fillColor, sf::Color outlineColor, std::string text);
	GUIButtonChangeState(GameContext& gameContext, sf::Vector2f positionRatio, Enums::eState currentState, Enums::eState newState, sf::Color fillColor, sf::Color outlineColor);
	~GUIButtonChangeState();

	virtual void clicked();

	virtual void drawCurrent(sf::RenderTarget & target);
private:
	Enums::eState mCurrentState;
	Enums::eState mNewState;

	std::string mText;

	sf::Color mFillColor;
	sf::Color mOutlineColor;
	sf::Font& mFont;
};

