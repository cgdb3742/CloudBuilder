#pragma once
#include "GUIButton.h"
#include "InstructionDraggableHandler.h"

class GUIInstructionTrashBin :
	public GUIButton,
	public InstructionDraggableHandler
{
public:
	GUIInstructionTrashBin(GameContext& gameContext, sf::Vector2f positionRatio);
	GUIInstructionTrashBin(GameContext& gameContext);
	~GUIInstructionTrashBin();

	virtual bool canGetFromDrag(sf::Vector2f mousePos);
	virtual InstructionSquare::InstructionSquarePtr getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr);

	virtual void drawCurrent(sf::RenderTarget & target);
};

