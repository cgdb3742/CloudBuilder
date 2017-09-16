#include "GUITestsModel.h"
#include "Level.h"
#include "Game.h"



GUITestsModel::GUITestsModel(GameContext & gameContext, sf::Vector2f positionRatio, Level& level) :
	GUIButton(gameContext, positionRatio),
	mLevel(level),
	mCurrentCloud(0),
	mStartingCloud(gameContext, gameContext.levelData.clouds[0]),
	mIsValidation(gameContext.levelData.isValidation),
	mWantAccept(false),
	mResultCloud(gameContext, gameContext.levelData.clouds[0])
{
	updateCloud();
}


GUITestsModel::~GUITestsModel()
{
}

void GUITestsModel::updateCloud()
{
	mCurrentCloud = mLevel.getCurrentCloud();
	mStartingCloud.convertFromString(mGameContext.levelData.clouds[mLevel.getCurrentCloud()]);

	if (mIsValidation)
	{
		mWantAccept = (mGameContext.levelData.results[mLevel.getCurrentCloud()] == L"Accept");
	}
	else
	{
		mResultCloud.convertFromString(mGameContext.levelData.results[mLevel.getCurrentCloud()]);
	}
}

void GUITestsModel::updateCurrent(sf::Time dt)
{
	if (mCurrentCloud != mLevel.getCurrentCloud())
	{
		updateCloud();
	}
}

void GUITestsModel::drawAccept(sf::RenderTarget & target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox)
{
	float size = std::min(boundingBox.x, boundingBox.y);
	float xmargin = (boundingBox.x - size) / 2.0f;
	float ymargin = (boundingBox.y - size) / 2.0f;

	sf::ConvexShape acceptLeft;
	acceptLeft.setPointCount(4);
	acceptLeft.setPoint(0, sf::Vector2f(0.125f, 0.625f));
	acceptLeft.setPoint(1, sf::Vector2f(0.375f, 0.875f));
	acceptLeft.setPoint(2, sf::Vector2f(0.375f, 0.625f));
	acceptLeft.setPoint(3, sf::Vector2f(0.25f, 0.5f));
	acceptLeft.scale(sf::Vector2f(size, size));
	acceptLeft.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	acceptLeft.setFillColor(sf::Color(0, 255, 0));
	target.draw(acceptLeft);

	sf::ConvexShape acceptRight;
	acceptRight.setPointCount(4);
	acceptRight.setPoint(0, sf::Vector2f(0.875f, 0.375f));
	acceptRight.setPoint(1, sf::Vector2f(0.375f, 0.875f));
	acceptRight.setPoint(2, sf::Vector2f(0.375f, 0.625f));
	acceptRight.setPoint(3, sf::Vector2f(0.75f, 0.25f));
	acceptRight.scale(sf::Vector2f(size, size));
	acceptRight.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	acceptRight.setFillColor(sf::Color(0, 255, 0));
	target.draw(acceptRight);
}

void GUITestsModel::drawReject(sf::RenderTarget & target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox)
{
	float size = std::min(boundingBox.x, boundingBox.y);
	float xmargin = (boundingBox.x - size) / 2.0f;
	float ymargin = (boundingBox.y - size) / 2.0f;

	sf::ConvexShape iconRejectBar;
	iconRejectBar.setPointCount(4);
	iconRejectBar.setPoint(0, sf::Vector2f(0.75f, 0.125f));
	iconRejectBar.setPoint(1, sf::Vector2f(0.125f, 0.75f));
	iconRejectBar.setPoint(2, sf::Vector2f(0.25f, 0.875f));
	iconRejectBar.setPoint(3, sf::Vector2f(0.875f, 0.25f));
	iconRejectBar.scale(sf::Vector2f(size, size));
	iconRejectBar.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	iconRejectBar.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectBar);

	sf::ConvexShape iconRejectUpLeft;
	iconRejectUpLeft.setPointCount(4);
	iconRejectUpLeft.setPoint(0, sf::Vector2f(0.125f, 0.25f));
	iconRejectUpLeft.setPoint(1, sf::Vector2f(0.375f, 0.5f));
	iconRejectUpLeft.setPoint(2, sf::Vector2f(0.5f, 0.375f));
	iconRejectUpLeft.setPoint(3, sf::Vector2f(0.25f, 0.125f));
	iconRejectUpLeft.scale(sf::Vector2f(size, size));
	iconRejectUpLeft.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	iconRejectUpLeft.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectUpLeft);

	sf::ConvexShape iconRejectDownRight;
	iconRejectDownRight.setPointCount(4);
	iconRejectDownRight.setPoint(0, sf::Vector2f(0.875f, 0.75f));
	iconRejectDownRight.setPoint(1, sf::Vector2f(0.625f, 0.5f));
	iconRejectDownRight.setPoint(2, sf::Vector2f(0.5f, 0.625f));
	iconRejectDownRight.setPoint(3, sf::Vector2f(0.75f, 0.875f));
	iconRejectDownRight.scale(sf::Vector2f(size, size));
	iconRejectDownRight.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	iconRejectDownRight.setFillColor(sf::Color(255, 0, 0));
	target.draw(iconRejectDownRight);
}

void GUITestsModel::drawArrow(sf::RenderTarget & target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox)
{
	float size = std::min(boundingBox.x, boundingBox.y);
	float xmargin = (boundingBox.x - size) / 2.0f;
	float ymargin = (boundingBox.y - size) / 2.0f;

	sf::RectangleShape rectangle(sf::Vector2f(size * 0.5f, size * 0.5f));
	rectangle.setPosition(topLeftCorner + sf::Vector2f(xmargin, ymargin + size * 0.25f));
	rectangle.setFillColor(sf::Color(0, 0, 0));
	target.draw(rectangle);

	sf::ConvexShape tip;
	tip.setPointCount(3);
	tip.setPoint(0, sf::Vector2f(0.5f, 0.0f));
	tip.setPoint(1, sf::Vector2f(0.5f, 1.0f));
	tip.setPoint(2, sf::Vector2f(1.0f, 0.5f));
	tip.scale(sf::Vector2f(size, size));
	tip.move(topLeftCorner + sf::Vector2f(xmargin, ymargin));
	tip.setFillColor(sf::Color(0, 0, 0));
	target.draw(tip);
}

void GUITestsModel::drawCurrent(sf::RenderTarget & target)
{
	float size = mBoundingBox.x / 5.0f;

	mStartingCloud.drawTo(target, mTopLeftCorner, sf::Vector2f(size * 2.0f, mBoundingBox.y));
	drawArrow(target, mTopLeftCorner + sf::Vector2f(2.125f * size, mBoundingBox.y * 3.0f / 8.0f), sf::Vector2f(size * 0.75f, mBoundingBox.y / 4.0f));

	if (mIsValidation)
	{
		if (mWantAccept)
		{
			drawAccept(target, mTopLeftCorner + sf::Vector2f(3.25f * size, mBoundingBox.y / 8.0f), sf::Vector2f(size * 1.5f, 3.0f * mBoundingBox.y / 4.0f));
		}
		else
		{
			drawReject(target, mTopLeftCorner + sf::Vector2f(3.25f * size, mBoundingBox.y / 8.0f), sf::Vector2f(size * 1.5f, 3.0f * mBoundingBox.y / 4.0f));
		}
	}
	else
	{
		mResultCloud.drawTo(target, mTopLeftCorner + sf::Vector2f(3.0f * size, 0.0f), sf::Vector2f(size * 2.0f, mBoundingBox.y));
	}
}
