#pragma once
#include "GUIButton.h"
class GUIOptionsLanguage :
	public GUIButton
{
public:
	GUIOptionsLanguage(GameContext& gameContext, sf::Vector2f positionRatio, unsigned int id, sf::Color normalFillColor, sf::Color selectedFillColor, sf::Color outlineColor);
	~GUIOptionsLanguage();

	virtual void clicked();

	virtual void drawCurrent(sf::RenderTarget & target);
private:
	unsigned int mId;

	sf::Color mNormalFillColor;
	sf::Color mSelectedFillColor;
	sf::Color mOutlineColor;

	sf::Font& mFont;
};

