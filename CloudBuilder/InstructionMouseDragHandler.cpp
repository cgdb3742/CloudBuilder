#include <iostream>
#include "InstructionMouseDragHandler.h"
#include "InstructionBoard.h"
#include "GUIInstructionCreatorContainer.h"
#include "InstructionSquare.h"


InstructionMouseDragHandler::InstructionMouseDragHandler(InstructionBoard& board, GUIInstructionCreatorContainer& creatorContainer) :
	mIsDragging(false),
	mDragged(nullptr),
	mBoard(board),
	mCreatorContainer(creatorContainer),
	mMousePos(sf::Vector2f(-1.0f, -1.0f)),
	mDragStart(sf::Vector2f(-2.0f, -2.0f))
{
}


InstructionMouseDragHandler::~InstructionMouseDragHandler()
{
}



bool InstructionMouseDragHandler::pick() //TODO Make available only during Build Mode
{
	if (mIsDragging || mLocked)
	{
		return false;
	}

	mDragged = mBoard.giveToDrag(mMousePos);

	if (mDragged != nullptr)
	{
		mIsDragging = true;
		mDragStart = mMousePos;
		updateChildsVector();
		setPositionChilds(mTopLeftCorner, mBoundingBox);
		std::cout << "Picked an InstructionSquare." << std::endl;
		return true;
	}

	mDragged = mCreatorContainer.giveToDrag(mMousePos);

	if (mDragged != nullptr)
	{
		mIsDragging = true;
		mDragStart = mMousePos;
		updateChildsVector();
		setPositionChilds(mTopLeftCorner, mBoundingBox);
		std::cout << "Picked an InstructionSquare." << std::endl;
		return true;
	}

	return false;
}


bool InstructionMouseDragHandler::drop(sf::Vector2f pos)
{
	if (!mIsDragging || mLocked)
	{
		return false;
	}

	if (mBoard.canGetFromDrag(pos))
	{
		mDragged = mBoard.getFromDrag(pos, std::move(mDragged));

		if (mDragged == nullptr)
		{
			mIsDragging = false;
			updateChildsVector();
			std::cout << "Dropped an InstructionSquare." << std::endl;
			return false;
		}
	}

	if (mBoard.canGetFromDrag(pos))
	{
		mDragged = mBoard.getFromDrag(pos, std::move(mDragged));

		if (mDragged == nullptr)
		{
			mIsDragging = false;
			updateChildsVector();
			std::cout << "Dropped an InstructionSquare." << std::endl;
			return true;
		}
	}

	if (pos != mDragStart) //If drop failed, try to drop at starting position, so InstructionSquares in InstructionBoard are not lost (especially starting points)
	{
		return drop(mDragStart);
	}

	mDragged = nullptr;
	mIsDragging = false;
	updateChildsVector();

	return false;
}

void InstructionMouseDragHandler::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		updateMousePos(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			updateMousePos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			pick();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			updateMousePos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			drop(mMousePos);
		}
		break;
	}
}

bool InstructionMouseDragHandler::updateMousePos(sf::Vector2f newMousePos)
{
	mMousePos = newMousePos;
	setPositionAll(mTopLeftCorner, mBoundingBox);
	return true;
}

//void InstructionMouseDragHandler::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
//{
//}

void InstructionMouseDragHandler::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	mBoundingBox = mBoard.getSquareSize();
	mTopLeftCorner = mMousePos - mBoundingBox / 2.0f;

}


void InstructionMouseDragHandler::updateChildsVector()
{
	mChilds.clear();

	if (mIsDragging)
	{
		mChilds.push_back(*(mDragged));
	}
}
