#pragma once

#include <map>
#include "InstructionDraggableHandler.h"
#include "GUIInstructionCreator.h"
#include "Enums.h"

class InstructionBoard;

class GUIInstructionCreatorContainer:
	public GameEntity,
	public InstructionDraggableHandler
{
public:
	GUIInstructionCreatorContainer(InstructionBoard& board);
	~GUIInstructionCreatorContainer();

	void setUpCreators();

	virtual sf::Vector2f computeChildsBoundingBox();
	//virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);

	virtual InstructionSquare::InstructionSquarePtr giveToDrag(sf::Vector2f mousePos);

	virtual void drawCurrent(sf::RenderTarget& target);
protected:
	virtual void updateChildsVector();

private:
	std::map<Enums::eInstruction, GUIInstructionCreator> mCreators;

	InstructionBoard& mBoard;
};

