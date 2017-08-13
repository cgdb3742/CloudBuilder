#include "InstructionDraggableHandler.h"
#include "InstructionSquare.h"


InstructionDraggableHandler::InstructionDraggableHandler()
{
}


InstructionDraggableHandler::~InstructionDraggableHandler()
{
}


InstructionSquare::InstructionSquarePtr InstructionDraggableHandler::giveToDrag(sf::Vector2f mousePos)
{
	return nullptr;
}

//bool InstructionDraggableHandler::getFromDrag(sf::Vector2f mousePos, std::unique_ptr<GameEntity> ptr)
//{
//	return false;
//}


bool InstructionDraggableHandler::canGetFromDrag(sf::Vector2f mousePos)
{
	return false;
}


InstructionSquare::InstructionSquarePtr InstructionDraggableHandler::getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr)
{
	return ptr;
}