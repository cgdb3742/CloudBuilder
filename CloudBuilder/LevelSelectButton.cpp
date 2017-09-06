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

	float iconBoxSize = std::min(mBoundingBox.x * 0.2f, mBoundingBox.y);

	sf::Text text;
	text.setFont(mFont);
	text.setString(std::to_string(mId) + " : " + mGameContext.gameData.levelName[mWorld - 1][mId - 1]);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	//text.setOrigin(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2.0f);
	float scale = std::min((mBoundingBox.x - iconBoxSize) / textRect.width, mBoundingBox.y / textRect.height);
	text.setOrigin(textRect.left, textRect.top + textRect.height / 2.0f);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + sf::Vector2f(0.05f * (mBoundingBox.x - iconBoxSize), mBoundingBox.y / 2.0f));
	target.draw(text);

	drawIcon(target, mTopLeftCorner + sf::Vector2f(mBoundingBox.x - iconBoxSize / 2.0f, mBoundingBox.y / 2.0f), sf::Vector2f(iconBoxSize, iconBoxSize));
}

void LevelSelectButton::drawIcon(sf::RenderTarget & target, sf::Vector2f center, sf::Vector2f maxBox)
{
	if (mGameContext.saveData.levelStatus[mWorld - 1][mId - 1] == Enums::eLevelStatus::Locked)
	{
		sf::RectangleShape base(sf::Vector2f(maxBox.x * 0.9f, maxBox.y * 0.6f));
		base.setPosition(center - sf::Vector2f(maxBox.x * 0.45f, maxBox.y * 0.15f));
		base.setFillColor(sf::Color(127, 127, 127));
		target.draw(base);

		sf::CircleShape lock(maxBox.x * 0.3f);
		lock.setPosition(center - sf::Vector2f(maxBox.x * 0.3f, maxBox.y * 0.45f));
		lock.setFillColor(sf::Color(127, 127, 127));
		target.draw(lock);
	}
	else if (mGameContext.saveData.levelStatus[mWorld - 1][mId - 1] == Enums::eLevelStatus::New)
	{
		sf::RectangleShape base(sf::Vector2f(maxBox.x * 0.2f, maxBox.y * 0.6f));
		base.setPosition(center - sf::Vector2f(maxBox.x * 0.1f, maxBox.y * 0.45f));
		base.setFillColor(sf::Color(255, 0, 0));
		target.draw(base);

		sf::CircleShape point(maxBox.x * 0.1f);
		point.setPosition(center - sf::Vector2f(maxBox.x * 0.1f, -maxBox.y * 0.25f));
		point.setFillColor(sf::Color(255, 0, 0));
		target.draw(point);
	}
	else if (mGameContext.saveData.levelStatus[mWorld - 1][mId - 1] == Enums::eLevelStatus::Complete)
	{
		sf::ConvexShape star;
		star.setPointCount(4);

		star.setPoint(0, sf::Vector2f(0.0f, -1.0f));
		star.setPoint(1, sf::Vector2f(-1.0f, 0.0f));
		star.setPoint(2, sf::Vector2f(0.0f, 1.0f));
		star.setPoint(3, sf::Vector2f(1.0f, 0.0f));

		star.scale(maxBox * 0.45f);
		star.move(center);
		star.setFillColor(sf::Color(255, 255, 0));
		target.draw(star);
	}
}
