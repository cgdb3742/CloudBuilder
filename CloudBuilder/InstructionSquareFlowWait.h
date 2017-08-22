#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowWait :
	public InstructionSquare
{
public:
	InstructionSquareFlowWait(GameContext& gameContext);
	InstructionSquareFlowWait(GameContext& gameContext, std::string source);
	~InstructionSquareFlowWait();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

