#include <iostream>
#include "LevelSelectButton.h"
#include "Game.h"
#include "StateLevelSelect.h"


LevelSelectButton::LevelSelectButton(GameContext& gameContext, sf::Vector2f positionRatio, StateLevelSelect& state, unsigned int world, unsigned int id) :
	GUIButton(gameContext, positionRatio),
	mState(state),
	mWorld(world),
	mId(id),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


LevelSelectButton::~LevelSelectButton()
{
}

void LevelSelectButton::clicked()
{
	mState.startLevel();
}

void LevelSelectButton::beginHover()
{
	std::cout << "Begin Hover." << std::endl;
	mState.selectLevel(mId);
}

void LevelSelectButton::endHover()
{
	std::cout << "End Hover." << std::endl;
	if (mState.getLevel() == mId)
	{
		mState.selectLevel(0);
	}
}

void LevelSelectButton::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);

	if (mGameContext.gameData.levelIsValidation[mWorld - 1][mId - 1])
	{
		background.setFillColor(sf::Color(63, 191, 255));
	}
	else
	{
		background.setFillColor(sf::Color(255, 191, 63));
	}

	background.setOutlineThickness(1.0f);
	background.setOutlineColor(sf::Color(0, 0, 0));

	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(std::to_string(mId) + " : " + mGameContext.gameData.levelName[mWorld - 1][mId - 1]);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//text.setOrigin(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2.0f);
	float scale = std::min(mBoundingBox.x / textRect.width, mBoundingBox.y / textRect.height);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + mBoundingBox / 2.0f);
	target.draw(text);
}
