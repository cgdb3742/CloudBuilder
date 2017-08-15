#include <iostream>
#include "GUILevelMenuTab.h"
#include "GUILevelMenu.h"
#include "Game.h"



//GUILevelMenuTab::GUILevelMenuTab():
//	mName("Undefined"),
//	mId(0)
//{
//}

//GUILevelMenuTab::GUILevelMenuTab(GameContext& gameContext, std::string name, unsigned int id, GUILevelMenu & menu):
//	GameEntity(gameContext),
//	mMenu(menu),
//	mName(name),
//	mId(id),
//	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
//{
//}

GUILevelMenuTab::GUILevelMenuTab(GameContext& gameContext, unsigned int id, GUILevelMenu & menu) :
	GameEntity(gameContext),
	mMenu(menu),
	mName(gameContext.gameData.levelTabName[id]),
	mId(id),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
	std::cout << "Creating GameEntity : GUILevelMenuTab." << std::endl;
}


GUILevelMenuTab::~GUILevelMenuTab()
{
}

void GUILevelMenuTab::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left && event.mouseButton.x > mTopLeftCorner.x && event.mouseButton.x < mTopLeftCorner.x + mBoundingBox.x && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
		{
			mMenu.changeSelection(mId);
		}
		break;
	}
}

void GUILevelMenuTab::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);

	switch (mId)
	{
	case 0: background.setFillColor(sf::Color(0, 191, 0, 127)); break;
	case 1: background.setFillColor(sf::Color(191, 0, 191, 127)); break;
	case 2: background.setFillColor(sf::Color(0, 191, 191, 127)); break;
	case 3: background.setFillColor(sf::Color(0, 0, 191, 127)); break;
	}

	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mName);
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
