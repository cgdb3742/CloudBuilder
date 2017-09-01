#pragma once
#include "GUIButton.h"

class StateLevelSelect;

class LevelSelectButton :
	public GUIButton
{
public:
	LevelSelectButton(GameContext& gameContext, sf::Vector2f positionRatio, StateLevelSelect& state, unsigned int world, unsigned int id);
	~LevelSelectButton();

	virtual void clicked();
	virtual void beginHover();
	virtual void endHover();

	virtual void drawCurrent(sf::RenderTarget& target);

private:
	unsigned int mWorld;
	unsigned int mId;

	StateLevelSelect& mState;

	sf::Font& mFont;
};

