#include <iostream>
#include "GameEntity.h"

//typedef std::unique_ptr<GameEntity> GameEntityPtr;

GameEntity::GameEntity():
	mChilds(std::vector<GameEntityRef>())
{
	//std::cout << "Creating GameEntity : unknown." << std::endl;
}


GameEntity::~GameEntity()
{
}

void GameEntity::handleEventAll(const sf::Event& event)
{
	handleEventCurrent(event);

	handleEventChilds(event);
}

void GameEntity::handleEventChilds(const sf::Event& event)
{
	for (unsigned int i = 0; i < mChilds.size(); i++)
	{
		mChilds[i].get().handleEventAll(event);
	}
}

void GameEntity::handleEventCurrent(const sf::Event& event)
{
}

//void GameEntity::handleEvent(const sf::Event& event)
//{
//	//for (GameEntity child : getChilds())
//	//{
//	//	child.handleEvent(const sf::Event& event);
//	//}
//}

void GameEntity::updateAll(sf::Time dt)
{
	updateCurrent(dt);

	updateChilds(dt);
}

void GameEntity::updateChilds(sf::Time dt)
{
	for (unsigned int i = 0; i < mChilds.size(); i++)
	{
		mChilds[i].get().updateAll(dt);
	}
}

void GameEntity::updateCurrent(sf::Time dt)
{
}

//void GameEntity::update(sf::Time dt)
//{
//	//for (GameEntity child : getChilds())
//	//{
//	//	child.update(sf::Time dt);
//	//}
//}

void GameEntity::drawAll(sf::RenderTarget & target)
{
	drawCurrent(target);

	drawChilds(target);
}

void GameEntity::drawChilds(sf::RenderTarget & target)
{
	for (unsigned int i = 0; i < mChilds.size(); i++)
	{
		mChilds[i].get().drawAll(target);
	}
}

void GameEntity::drawCurrent(sf::RenderTarget & target)
{
}

//void GameEntity::draw()
//void GameEntity::draw(sf::RenderTarget & target)
//{
//	//for (GameEntity child : getChilds())
//	//{
//	//	child.draw();
//	//}
//
//	drawCurrent(target);
//}

//void GameEntity::drawCurrent(sf::RenderTarget & target)
//{
//}

void GameEntity::setPositionAll(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	setPositionCurrent(minCorner, maxBox);

	//setPositionChilds(minCorner, maxBox);
	setPositionChilds(mTopLeftCorner, mBoundingBox);
}

void GameEntity::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	sf::Vector2f childBoundingBox = computeChildsBoundingBox();

	for (unsigned int i = 0; i < mChilds.size(); i++)
	{
		mChilds[i].get().setBoundingBoxCurrent(childBoundingBox);
		mChilds[i].get().setPositionAll(minCorner, maxBox);
	}
}

void GameEntity::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mTopLeftCorner = minCorner;
	mBoundingBox = maxBox;
}

sf::Vector2f GameEntity::computeChildsBoundingBox()
{
	return mBoundingBox;
}

void GameEntity::setBoundingBoxCurrent(sf::Vector2f boundingBox) //Empty : only used for components like GUIButton
{
}

//void GameEntity::setPosition(sf::Vector2f minCorner, sf::Vector2f maxBox)
//{
//	mTopLeftCorner = minCorner;
//	mBoundingBox = maxBox;
//}

sf::Vector2f GameEntity::getTopLeftCorner()
{
	return mTopLeftCorner;
}

sf::Vector2f GameEntity::getBoundingBox()
{
	return mBoundingBox;
}

void GameEntity::updateChildsVectorAll()
{
	updateChildsVector();

	for (unsigned int i = 0; i < mChilds.size(); i++)
	{
		mChilds[i].get().updateChildsVectorAll();
	}
}

std::vector<std::reference_wrapper<GameEntity>> GameEntity::getChilds()
{
	return mChilds;
}

void GameEntity::updateChildsVector()
{
}


