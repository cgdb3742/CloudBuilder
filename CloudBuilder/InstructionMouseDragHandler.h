#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "InstructionSquare.h"
#include "BuildLockable.h"

 //class InstructionDraggableHandler;
class InstructionBoard;
class GUIInstructionCreatorContainer;

//
//using InstructionDraggableHandlerRef = std::reference_wrapper<InstructionDraggableHandler>;

 class InstructionMouseDragHandler:
	public GameEntity,
	public BuildLockable
{
public:
	InstructionMouseDragHandler(GameContext& gameContext, InstructionBoard& board, GUIInstructionCreatorContainer& creatorContainer);
	~InstructionMouseDragHandler();

	bool pick();
	bool drop(sf::Vector2f pos);

	virtual void lock();

	virtual void handleEventCurrent(const sf::Event& event);
	virtual bool updateMousePos(sf::Vector2f newMousePos);

	//virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	sf::Vector2f mMousePos;
	sf::Vector2f mDragStart;
	bool mIsDragging;
	InstructionSquare::InstructionSquarePtr mDragged;

	InstructionBoard& mBoard;
	GUIInstructionCreatorContainer& mCreatorContainer;
};

//
//InstructionMouseDragHandler::InstructionMouseDragHandler() :
//	mIsDragging(false),
//	mDragged(nullptr)
//{
//}
//
//
//InstructionMouseDragHandler::~InstructionMouseDragHandler()
//{
//}
//
//
//inline bool InstructionMouseDragHandler::pick()
//{
//	return false;
//}
//
//
//inline bool InstructionMouseDragHandler::drop()
//{
//	return false;
//}