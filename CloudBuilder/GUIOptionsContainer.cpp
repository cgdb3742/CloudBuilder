#include "GUIOptionsContainer.h"



GUIOptionsContainer::GUIOptionsContainer(GameContext & gameContext) :
	GameEntity(gameContext),
	mToLevelSelect(gameContext, sf::Vector2f(0.875f, 0.75f), Enums::eState::Level, Enums::eState::LevelSelect, sf::Color(63,63,63), sf::Color(0,0,0))
{
}


GUIOptionsContainer::~GUIOptionsContainer()
{
}

void GUIOptionsContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(191 , 191, 191, 127));
	target.draw(background);
}

void GUIOptionsContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float margin = mBoundingBox.y / 10.0f;
	float xsize = (mBoundingBox.x - margin) / 4.0f - margin;
	float ysize = (mBoundingBox.y - margin) / 2.0f - margin;

	mToLevelSelect.setBoundingBoxCurrent(sf::Vector2f(xsize, ysize));
	mToLevelSelect.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
}

void GUIOptionsContainer::updateChildsVector()
{
	mChilds.clear();

	mChilds.push_back(mToLevelSelect);
}
