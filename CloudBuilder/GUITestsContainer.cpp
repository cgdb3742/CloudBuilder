#include "GUITestsContainer.h"



GUITestsContainer::GUITestsContainer(GameContext & gameContext, Level& level):
	GameEntity(gameContext),
	mModel(gameContext, sf::Vector2f(0.5f, 0.5f), level),
	mButtonUp(gameContext, sf::Vector2f(0.95f, 0.2f), level, -1),
	mButtonDown(gameContext, sf::Vector2f(0.95f, 0.8f), level, 1)

{
}


GUITestsContainer::~GUITestsContainer()
{
}

void GUITestsContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(0, 191, 191, 127));
	target.draw(background);
}

void GUITestsContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float minSize = std::min(mBoundingBox.x / 5.0f, mBoundingBox.y);
	float margin = minSize * 0.1f;

	sf::Vector2f childBoundingBox = sf::Vector2f(minSize / 2.0f - 2.0f * margin, minSize / 2.0f - 2.0f * margin);
	mButtonUp.setBoundingBoxCurrent(childBoundingBox);
	mButtonUp.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	mButtonDown.setBoundingBoxCurrent(childBoundingBox);
	mButtonDown.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));

	mModel.setBoundingBoxCurrent(maxBox - sf::Vector2f(minSize / 2.0f + 2.0f * margin, 2.0f * margin));
	mModel.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - sf::Vector2f(minSize / 2.0f + 2.0f * margin, 2.0f * margin));
}

void GUITestsContainer::updateChildsVector()
{
	mChilds.clear();

	mChilds.push_back(mButtonUp);
	mChilds.push_back(mButtonDown);
	mChilds.push_back(mModel);
}
