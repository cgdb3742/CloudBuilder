#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "InstructionSquare.h"

 class InstructionDraggableHandler//:
	 //public GameEntity
{
public:
	InstructionDraggableHandler();
	~InstructionDraggableHandler();

	virtual InstructionSquare::InstructionSquarePtr giveToDrag(sf::Vector2f mousePos);
	virtual bool canGetFromDrag(sf::Vector2f mousePos);
	virtual InstructionSquare::InstructionSquarePtr getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr);
	//virtual bool getFromDrag(sf::Vector2f mousePos, std::unique_ptr<GameEntity> ptr);
};

//
//InstructionDraggableHandler::InstructionDraggableHandler()
//{
//}
//
//
//InstructionDraggableHandler::~InstructionDraggableHandler()
//{
//}
//
//
//std::unique_ptr InstructionDraggableHandler::giveToDrag(sf::Vector2f mousePos)
//{
//	return nullptr;
//}
//
////bool InstructionDraggableHandler::getFromDrag(sf::Vector2f mousePos, std::unique_ptr<GameEntity> ptr)
////{
////	return false;
////}
//
//
//bool InstructionDraggableHandler::canGetFromDrag(sf::Vector2f mousePos)
//{
//	return false;
//}
//
//
//std::unique_ptr InstructionDraggableHandler::getFromDrag(sf::Vector2f mousePos, std::unique_ptr ptr)
//{
//	return ptr;
//}
