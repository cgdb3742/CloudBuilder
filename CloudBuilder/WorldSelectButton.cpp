#include "WorldSelectButton.h"
#include "Game.h"
#include "StateLevelSelect.h"


WorldSelectButton::WorldSelectButton(GameContext& gameContext, sf::Vector2f positionRatio, StateLevelSelect& state, unsigned int id):
	GUIButton(gameContext, positionRatio),
	mState(state),
	mId(id),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


WorldSelectButton::~WorldSelectButton()
{
}

void WorldSelectButton::clicked()
{
	mState.selectWorld(mId);
}

void WorldSelectButton::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);

	if (mState.getWorld() == mId)
	{
		background.setFillColor(sf::Color(255, 255, 191));
	}
	else
	{
		background.setFillColor(sf::Color(127, 127, 63));
	}

	background.setOutlineThickness(1.0f);
	background.setOutlineColor(sf::Color(0, 0, 0));

	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(std::to_wstring(mId) + L" : " + mGameContext.gameData.worldName[mId - 1]);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	//text.setOrigin(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2.0f);
	float scale = std::min(mBoundingBox.x / textRect.width, mBoundingBox.y / textRect.height);
	text.setOrigin(textRect.left, textRect.top + textRect.height / 2.0f);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + sf::Vector2f(0.05f * mBoundingBox.x, mBoundingBox.y / 2.0f));
	target.draw(text);
}
