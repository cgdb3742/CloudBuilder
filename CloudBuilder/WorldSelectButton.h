#pragma once
#include "GUIButton.h"

class StateLevelSelect;

class WorldSelectButton :
	public GUIButton
{
public:
	WorldSelectButton(GameContext& gameContext, sf::Vector2f positionRatio, StateLevelSelect& state, unsigned int id);
	~WorldSelectButton();

	virtual void clicked();

	virtual void drawCurrent(sf::RenderTarget& target);

private:
	unsigned int mId;

	StateLevelSelect& mState;

	sf::Font& mFont;
};

