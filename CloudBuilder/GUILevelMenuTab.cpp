#include "GUILevelMenuTab.h"
#include "GUILevelMenu.h"



//GUILevelMenuTab::GUILevelMenuTab():
//	mName("Undefined"),
//	mId(0)
//{
//}

GUILevelMenuTab::GUILevelMenuTab(std::string name, unsigned int id, GUILevelMenu & menu):
	mMenu(menu),
	mName(name),
	mId(id)
{
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

	//TODO Draw tab label

	target.draw(background);
}
