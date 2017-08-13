#include "GUIInfosTopic.h"
#include "GUIInfosContainer.h"



GUIInfosTopic::GUIInfosTopic(GUIInfosContainer & container, int id, std::string title, sf::Vector2f positionRatio):
	GUIButton(positionRatio),
	mContainer(container),
	mId(id),
	mTitle(title)
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

	//TODO Draw topic title
}
