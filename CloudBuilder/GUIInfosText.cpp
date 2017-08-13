#include "GUIInfosText.h"



GUIInfosText::GUIInfosText(sf::Vector2f positionRatio):
	GUIButton(positionRatio),
	mCompleteString(""),
	mCurrentLength(0),
	mCurrentString(""),
	mWrappedString(""),
	mTimerShow(0.0f),
	mMaxTimerShow(0.2f)
{
}


GUIInfosText::~GUIInfosText()
{
}

void GUIInfosText::updateCurrent(sf::Time dt)
{
	if (mCurrentLength < mCompleteString.size())
	{
		mTimerShow += dt.asSeconds();

		while (mTimerShow >= mMaxTimerShow)
		{
			mTimerShow -= mMaxTimerShow;
			mCurrentLength++;
			mCurrentString = mCompleteString.substr(0, mCurrentLength);
			wrapCurrentString();
		}
	}
}

void GUIInfosText::clicked()
{
	showAll();
}

//void GUIInfosText::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Left && event.mouseButton.x > mTopLeftCorner.x && event.mouseButton.x < mTopLeftCorner.x + mBoundingBox.x && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
//		{
//			showAll();
//		}
//		break;
//	}
//}

void GUIInfosText::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape button(mBoundingBox);
	button.setPosition(mTopLeftCorner);
	button.setFillColor(sf::Color(0, 191, 0));
	button.setOutlineThickness(1.0f);
	button.setOutlineColor(sf::Color(0, 255, 0));
	target.draw(button);

	//TODO Draw text
}

void GUIInfosText::setNewText(std::string newString)
{
	mCompleteString = newString;
	mCurrentLength = 0;
	mCurrentString = "";
	mTimerShow = 0.0f;
}

void GUIInfosText::showAll()
{
	mCurrentString = mCompleteString;
	mCurrentLength = mCompleteString.size();
	mTimerShow = 0.0f;
	wrapCurrentString();
}

void GUIInfosText::wrapCurrentString()
{
	//TODO Wrap the current string to display it inside mBoundingBox
}
