#include "GUIButton.h"



GUIButton::GUIButton(GameContext& gameContext, sf::Vector2f positionRatio):
	GameEntity(gameContext),
	mIsHovered(false),
	mPositionRatio(positionRatio)
{
}


GUIButton::~GUIButton()
{
}

void GUIButton::clicked()
{
}

void GUIButton::beginHover()
{
}

void GUIButton::endHover()
{
}

void GUIButton::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		if (containsPoint(sf::Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))))
		{
			if (!mIsHovered)
			{
				mIsHovered = true;
				beginHover();
			}
		}
		else
		{
			if (mIsHovered)
			{
				mIsHovered = false;
				endHover();
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left && containsPoint(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
		{
			clicked();
		}
		break;
	case sf::Event::TouchMoved:
		if (event.touch.finger == 0 && containsPoint(sf::Vector2f(static_cast<float>(event.touch.x), static_cast<float>(event.touch.y))))
		{
			if (!mIsHovered)
			{
				mIsHovered = true;
				beginHover();
			}
		}
		else
		{
			if (mIsHovered)
			{
				mIsHovered = false;
				endHover();
			}
		}
		break;
	case sf::Event::TouchEnded:
		if (event.touch.finger == 0 && containsPoint(sf::Vector2f(static_cast<float>(event.touch.x), static_cast<float>(event.touch.y))))
		{
			clicked();
		}
	}
}

void GUIButton::setBoundingBoxCurrent(sf::Vector2f boundingBox)
{
	mBoundingBox = boundingBox;
}

void GUIButton::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mTopLeftCorner.x = minCorner.x + mPositionRatio.x * maxBox.x - mBoundingBox.x / 2.0f;
	mTopLeftCorner.y = minCorner.y + mPositionRatio.y * maxBox.y - mBoundingBox.y / 2.0f;
}

bool GUIButton::containsPoint(sf::Vector2f point)
{
	//Rapid check for obvious cases
	if (point.x <= mTopLeftCorner.x || point.x >= mTopLeftCorner.x + mBoundingBox.x || point.y <= mTopLeftCorner.y || point.y >= mTopLeftCorner.y + mBoundingBox.y)
	{
		return false;
	}

	return true;
}
