#include "GUIInfosTopic.h"
#include "GUIInfosContainer.h"
#include "Game.h"



GUIInfosTopic::GUIInfosTopic(GameContext& gameContext, GUIInfosContainer & container, int id, std::string title, sf::Vector2f positionRatio):
	GUIButton(gameContext, positionRatio),
	mContainer(container),
	mId(id),
	mTitle(title),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


GUIInfosTopic::~GUIInfosTopic()
{
}

void GUIInfosTopic::clicked()
{
	mContainer.changeTopic(mId);
}

//void GUIInfosTopic::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Left && event.mouseButton.x > mTopLeftCorner.x && event.mouseButton.x < mTopLeftCorner.x + mBoundingBox.x && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
//		{
//			mContainer.changeTopic(mId);
//		}
//		break;
//	}
//}

void GUIInfosTopic::drawCurrent(sf::RenderTarget & target)
{
	

	sf::RectangleShape button(mBoundingBox);
	button.setPosition(mTopLeftCorner);
	button.setFillColor(sf::Color(0, 191, 0));
	button.setOutlineThickness(1.0f);
	button.setOutlineColor(sf::Color(0, 255, 0));
	target.draw(button);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mTitle);
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
