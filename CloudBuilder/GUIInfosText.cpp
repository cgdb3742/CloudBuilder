#include <iostream>
#include "GUIInfosText.h"
#include "Game.h"



GUIInfosText::GUIInfosText(GameContext& gameContext, sf::Vector2f positionRatio):
	GUIButton(gameContext, positionRatio),
	mCompleteString(L""),
	mCurrentLength(0),
	mCurrentString(L""),
	mWrappedString(L""),
	mTimerShow(0.0f),
	mMaxTimerShow(0.05f),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


GUIInfosText::~GUIInfosText()
{
}

void GUIInfosText::updateCurrent(sf::Time dt)
{
	if (mCurrentLength < mWrappedString.size())
	{
		mTimerShow += dt.asSeconds();

		while (mTimerShow >= mMaxTimerShow)
		{
			mTimerShow -= mMaxTimerShow;
			mCurrentLength++;
			mCurrentString = mWrappedString.substr(0, mCurrentLength);
			//wrapCompleteString();
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

	sf::Text text;
	text.setFont(mFont);
	text.setString(mWrappedString);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//float scale = mBoundingBox.x / 480.0f;
	float scale = std::min(mBoundingBox.x / 480.0f, mBoundingBox.y / textRect.height);
	text.scale(sf::Vector2f(scale, scale) * 0.95f);
	text.setPosition(mTopLeftCorner + mBoundingBox / 2.0f);
	text.setString(mCurrentString);
	target.draw(text);
}

void GUIInfosText::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	GUIButton::setPositionCurrent(minCorner, maxBox);
	wrapCompleteString();
}

void GUIInfosText::setNewText(std::wstring newString)
{
	mCompleteString = newString;
	mCurrentLength = 0;
	mCurrentString = L"";
	mTimerShow = 0.0f;
	wrapCompleteString();
}

void GUIInfosText::showAll()
{
	mCurrentString = mWrappedString;
	mCurrentLength = mWrappedString.size();
	mTimerShow = 0.0f;
	//wrapCompleteString();
}

void GUIInfosText::wrapCompleteString() //TODO Why wrapped text begin by /n ?
{
	size_t nextSpace = mCompleteString.find(L" ");

	std::wstring res = L"";
	std::wstring currentLine = mCompleteString.substr(0, nextSpace);
	size_t prevSpace = nextSpace;
	nextSpace = mCompleteString.find(L" ", nextSpace + 1);

	sf::Text text;
	text.setFont(mFont);
	text.setString(res);
	text.setCharacterSize(16);
	text.scale(mBoundingBox / 480.0f); //Note : only width is useful here

	while (prevSpace != std::wstring::npos)
	{
		std::wstring currentWord = mCompleteString.substr(prevSpace + 1, nextSpace - prevSpace - 1);
		text.setString(currentLine + L" " + currentWord);

		sf::FloatRect textRect = text.getGlobalBounds();

		if (textRect.width >= mBoundingBox.x * 0.95f)
		{
			//std::cout << textRect.width << std::endl;
			res += L"\n" + currentLine;
			currentLine = currentWord;
		}
		else
		{
			currentLine += L" " + currentWord;
		}

		prevSpace = nextSpace;
		nextSpace = mCompleteString.find(L" ", nextSpace + 1);
	}

	res += L"\n" + currentLine;
	mWrappedString = res;

	//std::cout << res << std::endl;
}
