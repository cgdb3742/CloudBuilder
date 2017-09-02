#include "GUIInstructionReset.h"
#include "Level.h"




GUIInstructionReset::GUIInstructionReset(GameContext & gameContext, sf::Vector2f positionRatio, Level& level):
	GUIButton(gameContext, positionRatio),
	mLevel(level)
{
}

GUIInstructionReset::GUIInstructionReset(GameContext & gameContext, Level& level) :
	GUIButton(gameContext, sf::Vector2f(0.0f, 0.0f)),
	mLevel(level)
{
}

GUIInstructionReset::~GUIInstructionReset()
{
}

void GUIInstructionReset::clicked()
{
	mLevel.resetBoardFromStart();
}

void GUIInstructionReset::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(255, 0, 255));
	target.draw(background);

	sf::RectangleShape square(mBoundingBox*3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 63, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	for (unsigned int i = 0; i < 8; i++)
	{
		sf::ConvexShape rect;
		rect.setPointCount(4);
		rect.setPoint(0, sf::Vector2f(0.45f, 0.05f));
		rect.setPoint(1, sf::Vector2f(0.45f, -0.05f));
		rect.setPoint(2, sf::Vector2f(0.25f, -0.05f));
		rect.setPoint(3, sf::Vector2f(0.25f, 0.05f));
		rect.rotate(static_cast<float>(i) * 45.0f);
		rect.scale(mBoundingBox*3.0f / 4.0f);
		rect.move(mTopLeftCorner + mBoundingBox / 2.0f);
		rect.setFillColor(sf::Color(255, 255, 255));
		target.draw(rect);
	}
}
