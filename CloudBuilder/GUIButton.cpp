#include "GUIButton.h"



GUIButton::GUIButton(sf::Vector2f positionRatio):
	mPositionRatio(positionRatio)
{
}


GUIButton::~GUIButton()
{
}

void GUIButton::clicked()
{
}

void GUIButton::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left && containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			clicked();
		}
		break;
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
