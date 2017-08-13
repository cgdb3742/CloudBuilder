#pragma once
#include "GUIButton.h"
#include "InstructionDraggableHandler.h"
#include "InstructionSquare.h"
#include "Enums.h"

class GUIInstructionCreator :
	public GUIButton,
	public InstructionDraggableHandler
{
public:
	GUIInstructionCreator();
	GUIInstructionCreator(Enums::eInstruction type, sf::Vector2f positionRatio);
	GUIInstructionCreator(const GUIInstructionCreator& toCopy);
	~GUIInstructionCreator();

	virtual InstructionSquare::InstructionSquarePtr giveToDrag(sf::Vector2f mousePos);

	InstructionSquare::InstructionSquarePtr createNewInstruction();

	//virtual void setSquareSize(sf::Vector2f newSize);
	//virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);

	virtual void drawCurrent(sf::RenderTarget& target);
protected:
	virtual void updateChildsVector();
private:
	Enums::eInstruction mType;
	//InstructionSquare::InstructionSquarePtr mInstruction;
	InstructionSquare::InstructionSquarePtr mInstruction;

	//TODO Trash bin and Reset buttons
};

