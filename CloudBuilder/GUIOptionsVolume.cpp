#include "GUIOptionsVolume.h"
#include "Game.h"



GUIOptionsVolume::GUIOptionsVolume(GameContext& gameContext, sf::Vector2f positionRatio, bool controlMusic):
	GUIButton(gameContext, positionRatio),
	mControlMusic(controlMusic),
	mVolumeRatio(controlMusic ? (gameContext.dataReader.getSaveData().musicVolume) : (gameContext.dataReader.getSaveData().soundVolume)),
	mIsDragged(false),
	mBarWidthRatio(0.2f),
	mMinPos(0.0f),
	mMaxPos(1.0f),
	mCurrentPos(1.0f)
{
}


GUIOptionsVolume::~GUIOptionsVolume()
{
}

void GUIOptionsVolume::beginDrag(float mousePosx)
{
	mIsDragged = true;

	updateDrag(mousePosx);
}

void GUIOptionsVolume::updateDrag(float mousePosx)
{
	if (mMaxPos == mMinPos)
	{
		return;
	}

	mCurrentPos = std::max(mMinPos, std::min(mMaxPos, mousePosx));
	mVolumeRatio = (mCurrentPos - mMinPos) / (mMaxPos - mMinPos);
	
	if (mControlMusic)
	{
		mGameContext.resourceHandler.setMusicVolume(mVolumeRatio);
	}
	else
	{
		mGameContext.resourceHandler.setSoundVolume(mVolumeRatio);
	}
}

void GUIOptionsVolume::endDrag(float mousePosx)
{
	updateDrag(mousePosx);

	mIsDragged = false;

	if (mControlMusic)
	{
		mGameContext.dataReader.writeMusicVolume(mVolumeRatio);
	}
	else
	{
		mGameContext.dataReader.writeSoundVolume(mVolumeRatio);
	}
}

void GUIOptionsVolume::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left && !mIsDragged && event.mouseButton.x > mCurrentPos - mBoundingBox.y / 2.0f && event.mouseButton.x < mCurrentPos + mBoundingBox.y / 2.0f && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
		{
			beginDrag(static_cast<float>(event.mouseButton.x));
		}
		break;
	case sf::Event::MouseMoved:
		if (mIsDragged)
		{
			updateDrag(static_cast<float>(event.mouseMove.x));
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left && mIsDragged)
		{
			endDrag(static_cast<float>(event.mouseButton.x));
		}
		break;
	case sf::Event::TouchBegan:
		if (event.touch.finger == 0 && !mIsDragged && event.touch.x > mCurrentPos - mBoundingBox.y / 2.0f && event.touch.x < mCurrentPos + mBoundingBox.y / 2.0f && event.touch.y > mTopLeftCorner.y && event.touch.y < mTopLeftCorner.y + mBoundingBox.y)
		{
			beginDrag(static_cast<float>(event.touch.x));
		}
		break;
	case sf::Event::TouchMoved:
		if (event.touch.finger == 0 && mIsDragged)
		{
			updateDrag(static_cast<float>(event.touch.x));
		}
		break;
	case sf::Event::TouchEnded:
		if (event.touch.finger == 0 && mIsDragged)
		{
			endDrag(static_cast<float>(event.touch.x));
		}
		break;
	}
}

void GUIOptionsVolume::drawCurrent(sf::RenderTarget & target)
{
	float barWidth = mBarWidthRatio * mBoundingBox.y;
	sf::RectangleShape bar(sf::Vector2f(mBoundingBox.x - mBoundingBox.y + barWidth, barWidth));
	bar.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.y - barWidth, mBoundingBox.y - barWidth) / 2.0f);
	bar.setFillColor(sf::Color(63, 63, 63));
	target.draw(bar);

	sf::RectangleShape square(sf::Vector2f(mBoundingBox.y, mBoundingBox.y));
	square.setPosition(sf::Vector2f(mCurrentPos - mBoundingBox.y / 2.0f, mTopLeftCorner.y));
	square.setFillColor(sf::Color(191, 191, 191));
	target.draw(square);
}

void GUIOptionsVolume::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	GUIButton::setPositionCurrent(minCorner, maxBox);

	mMinPos = mTopLeftCorner.x + mBoundingBox.y / 2.0f;
	mMaxPos = mTopLeftCorner.x + mBoundingBox.x - mBoundingBox.y / 2.0f;
	mCurrentPos = mMinPos + mVolumeRatio * (mMaxPos - mMinPos);
}
