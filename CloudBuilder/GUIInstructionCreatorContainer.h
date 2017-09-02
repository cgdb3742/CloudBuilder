#pragma once

#include <map>
#include "InstructionDraggableHandler.h"
#include "GUIInstructionCreator.h"
#include "GUIInstructionTrashBin.h"
#include "GUIInstructionReset.h"
#include "Enums.h"

class InstructionBoard;

class GUIInstructionCreatorContainer:
	public GameEntity,
	public InstructionDraggableHandler
{
public:
	GUIInstructionCreatorContainer(GameContext& gameContext, Level& level, InstructionBoard& board);
	~GUIInstructionCreatorContainer();

	void setUpCreators();

	virtual sf::Vector2f computeChildsBoundingBox();
	//virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);

	virtual bool canGetFromDrag(sf::Vector2f mousePos);
	InstructionSquare::InstructionSquarePtr getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr);
	virtual InstructionSquare::InstructionSquarePtr giveToDrag(sf::Vector2f mousePos);

	virtual void drawCurrent(sf::RenderTarget& target);
protected:
	virtual void updateChildsVector();

private:
	std::map<Enums::eInstruction, GUIInstructionCreator> mCreators;
	GUIInstructionTrashBin mTrashBin;
	GUIInstructionReset mReset;

	InstructionBoard& mBoard;
};

