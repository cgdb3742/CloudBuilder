#include "PopUpMessage.h"
#include "Game.h"
#include "StateMachine.h"


PopUpMessage::PopUpMessage(GameContext& gameContext, sf::Vector2f positionRatio, PopUpData messageData):
	GUIButton(gameContext, positionRatio),
	mText(messageData.mainMessage),
	mButton(gameContext, sf::Vector2f(0.5f,0.8f), messageData),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


PopUpMessage::~PopUpMessage()
{
}

sf::Vector2f PopUpMessage::computeChildsBoundingBox()
{
	return sf::Vector2f(mBoundingBox.x / 2.0f, mBoundingBox.y / 8.0f);
}

void PopUpMessage::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(63, 63, 63));
	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mText);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	float scale = std::min(mBoundingBox.x / textRect.width, (mBoundingBox.y / textRect.height) *3.0f / 4.0f);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.x / 2.0f, mBoundingBox.y * 3.0f / 8.0f));
	target.draw(text);
}

void PopUpMessage::updateChildsVector()
{
	mChilds.clear();

	mChilds.push_back(mButton);
}
